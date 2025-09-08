#include "include/arg_parser.hpp"
#include "include/file_reader.hpp"
#include "include/matcher.hpp"
#include "include/line_processor.hpp"
#include "include/grep_error.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Tokenize input, preserving quoted strings
std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;
    char quote_char = '\0';
    bool escape = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (escape) {
            token += c;
            escape = false;
            continue;
        }

        if (c == '\\') {
            escape = true;
            continue;
        }

        if (c == '"' || c == '\'') {
            if (!in_quotes) {
                in_quotes = true;
                quote_char = c;
                continue;
            }
            if (c == quote_char) {
                in_quotes = false;
                quote_char = '\0';
                continue;
            }
        }

        if (std::isspace(c) && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }

            continue;
        }

        token += c;
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

// glob patterns (e.g., *.cpp) 
std::vector<std::string> expand_globs(const std::vector<std::string>& tokens) {
    std::vector<std::string> expanded;
    for (const auto& token : tokens) {
        if (token.find('*') != std::string::npos || token.find('?') != std::string::npos) {
            try {
                fs::path pattern_path = token;
                std::string parent = pattern_path.has_parent_path() ? pattern_path.parent_path().string() : ".";
                bool matched = false;
                for (const auto& entry : fs::directory_iterator(parent)) {
                    if (fs::is_regular_file(entry) &&
                        std::regex_match(entry.path().filename().string(),
                                         std::regex(token.substr(parent == "." ? 0 : parent.length() + 1),
                                                    std::regex::ECMAScript))) {
                        expanded.push_back(fs::absolute(entry.path()).string());
                        matched = true;
                    }
                }

                if (!matched) {
                    expanded.push_back(token); // No matches, keep original token
                }
            } catch (const fs::filesystem_error&) {
                expanded.push_back(token); // On error, keep original token
            }
        } 
        else {
            expanded.push_back(token);
        }
    }

    return expanded;
}

int main() {
    std::string line;
    while (true) {
        std::cout << ">> ";
        std::cout.flush();
        if (!std::getline(std::cin, line)) {
            break; //  EOF (Ctrl+D)
        }

        // empty input
        if (line.empty()) {
            continue;
        }

        // exit command
        if (line == "exit") {
            break;
        }

        // Tokenize input, preserving quotes
        std::vector<std::string> tokens = tokenize(line);

        // if first token is "grep"
        if (tokens.empty() || tokens[0] != "grep") {
            std::cerr << "Error: Command must start with 'grep'" << std::endl;
            continue;
        }

        //  glob patterns
        tokens = expand_globs(tokens);

        // tokens to argv format
        std::vector<char*> argv;
        std::vector<std::string> token_storage = tokens; // Keep tokens alive
        for (auto& t : token_storage) {
            argv.push_back(t.data());
        }

        argv.push_back(nullptr);

        try {
            // arguments parsing
            args arguments = arg_parser::parse(argv.size() - 1, argv.data());

            // grep command processing
            matcher pattern_matcher(arguments.pattern, arguments.case_insensitive, arguments.whole_word,
                                   arguments.whole_line, arguments.invert_match);
            line_processor processor(pattern_matcher, arguments.context_before, arguments.context_after,
                                    arguments.list_files, arguments.count_matches, arguments.color);

            std::string current_file;
            file_reader::read(arguments.paths, arguments.recursive, arguments.include_extensions,
                [&processor, &current_file](const std::string& filepath, const std::string& line, size_t line_number) {
                    if (current_file != filepath && !current_file.empty()) {
                        processor.flush_file(current_file);
                    }

                    current_file = filepath;
                    processor.process(filepath, line, line_number);
                });

            if (!current_file.empty()) {
                processor.flush_file(current_file);
            }

            if (arguments.count_matches && arguments.paths.size() > 1) {
                size_t total = 0;
                for (const auto& [file, count] : processor.get_counts()) {
                    total += count;
                }

                std::cout << "Total matches: " << total << std::endl;
            }
        } catch (const grep_error& e) {
            std::cerr << "Error [" << (e.get_category() == grep_error::category::argument ? "argument" :
                                       e.get_category() == grep_error::category::file ? "file" :
                                       e.get_category() == grep_error::category::regex ? "regex" : "system")
                      << "]: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error [system]: " << e.what() << std::endl;
        }
    }
    
    return 0;
}