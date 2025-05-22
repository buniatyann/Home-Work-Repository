#include "include/FileSystem.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <cstdlib>

std::vector<std::string> split(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;
    char quote_char = '\0';

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if ((c == '"' || c == '\'') && (i == 0 || input[i-1] != '\\')) {
            if (!in_quotes) {
                in_quotes = true;
                quote_char = c;
            } else if (quote_char == c) {
                in_quotes = false;
                quote_char = '\0';
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        } else if ((c == '>' || (c == '>' && i + 1 < input.length() && input[i+1] == '>')) && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(c == '>' && input[i+1] == '>' ? ">>" : ">");
            if (c == '>' && input[i+1] == '>') {
                ++i;
            }
        } else if (c == ' ' && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    for (auto& t : tokens) {
        if (t.length() >= 2 && ((t.front() == '"' && t.back() == '"') || (t.front() == '\'' && t.back() == '\''))) {
            t = t.substr(1, t.length() - 2);
        }
    }

    return tokens;
}

void display_help() {
    std::cout << "Available commands:\n"
              << "  cd <path>                    Change current directory (empty for root)\n"
              << "  touch <file>                 Create or update timestamp of a file\n"
              << "  mkdir <dir>                  Create a new directory\n"
              << "  rm [-rf] <path>              Remove a file or directory (-r: recursive, -f: force, can combine as -rf)\n"
              << "  cp [-rf] <src> <dst>         Copy a file or directory (-r: recursive, -f: force, can combine as -rf)\n"
              << "  mv [-f] <src> <dst>          Move or rename a file or directory (-f: force)\n"
              << "  cat <file>                   Display file contents\n"
              << "  ln <target> <link>           Create a symbolic link\n"
              << "  chmod <mode> <path>          Change permissions (e.g., 755)\n"
              << "  ls [path]                    List directory contents (simple)\n"
              << "  ll                           List directory contents (detailed)\n"
              << "  pwd                          Print current working directory\n"
              << "  echo <text> [> file | >> file]  Output text to stdout or file\n"
              << "  help                         Show this help message\n"
              << "  exit                         Quit the program\n";
}

bool process_command(FileSystem& fs, const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        return true;
    }

    using command = std::function<bool(const std::vector<std::string>&)>;
    const std::string& cmd = tokens[0];
    std::unordered_map<std::string, command> commands = {
        {"cd", [&](const std::vector<std::string>& args) {
            if (args.size() > 2) {
                std::cerr << "Error: cd expects 0 or 1 argument\n";
                return false;
            }
            
            return fs.cd(args.size() == 1 ? "" : args[1]);
        }},
        {"touch", [&](const std::vector<std::string>& args) {
            if (args.size() != 2) {
                std::cerr << "Error: touch expects 1 argument\n";
                return false;
            }
            
            return fs.touch(args[1]);
        }},
        {"mkdir", [&](const std::vector<std::string>& args) {
            if (args.size() != 2) {
                std::cerr << "Error: mkdir expects 1 argument\n";
                return false;
            }
            
            return fs.mkdir(args[1]);
        }},
        {"rm", [&](const std::vector<std::string>& args) {
            FileSystem::remove_opt_t opts;
            std::size_t arg_start = 1;
            for (; arg_start < args.size() && args[arg_start][0] == '-'; ++arg_start) {
                const std::string& flag = args[arg_start];
                if (flag == "-r") {
                    opts.recursive = true;
                } 
                else if (flag == "-f") {
                    opts.force = true;
                } 
                else if (flag.length() > 1) {
                    for (size_t i = 1; i < flag.length(); ++i) {
                        char f = flag[i];
                        if (f == 'r') {
                            opts.recursive = true;
                        } 
                        else if (f == 'f') {
                            opts.force = true;
                        } 
                        else {
                            std::cerr << "Error: Unknown flag '-" << f << "' for rm\n";
                            return false;
                        }
                    }
                } 
                else {
                    std::cerr << "Error: Unknown flag '" << flag << "' for rm\n";
                    return false;
                }
            }
            
            if (arg_start + 1 != args.size()) {
                std::cerr << "Error: rm expects 1 path argument\n";
                return false;
            }
            
            return fs.rm(args[arg_start], opts);
        }},
        {"cp", [&](const std::vector<std::string>& args) {
            FileSystem::copy_opt_t opts;
            std::size_t arg_start = 1;
            for (; arg_start < args.size() && args[arg_start][0] == '-'; ++arg_start) {
                const std::string& flag = args[arg_start];
                if (flag == "-r") {
                    opts.recursive = true;
                } 
                else if (flag == "-f") {
                    opts.force = true;
                } 
                else if (flag.length() > 1) {
                    for (size_t i = 1; i < flag.length(); ++i) {
                        char f = flag[i];
                        if (f == 'r') {
                            opts.recursive = true;
                        } 
                        else if (f == 'f') {
                            opts.force = true;
                        } 
                        else {
                            std::cerr << "Error: Unknown flag '-" << f << "' for cp\n";
                            return false;
                        }
                    }
                } 
                else {
                    std::cerr << "Error: Unknown flag '" << flag << "' for cp\n";
                    return false;
                }
            }
            if (arg_start + 2 != args.size()) {
                std::cerr << "Error: cp expects 2 arguments\n";
                return false;
            }
            
            return fs.cp(args[arg_start], args[arg_start + 1], opts);
        }},
        {"mv", [&](const std::vector<std::string>& args) {
            FileSystem::move_opt_t opts;
            std::size_t arg_start = 1;
            for (; arg_start < args.size() && args[arg_start][0] == '-'; ++arg_start) {
                const std::string& flag = args[arg_start];
                if (flag == "-f") {
                    opts.force = true;
                } 
                else if (flag.length() > 1) {
                    for (size_t i = 1; i < flag.length(); ++i) {
                        char f = flag[i];
                        if (f == 'f') {
                            opts.force = true;
                        } 
                        else {
                            std::cerr << "Error: Unknown flag '-" << f << "' for mv\n";
                            return false;
                        }
                    }
                } 
                else {
                    std::cerr << "Error: Unknown flag '" << flag << "' for mv\n";
                    return false;
                }
            }
            if (arg_start + 2 != args.size()) {
                std::cerr << "Error: mv expects 2 arguments\n";
                return false;
            }
            
            return fs.mv(args[arg_start], args[arg_start + 1], opts);
        }},
        {"cat", [&](const std::vector<std::string>& args) {
            if (args.size() != 2) {
                std::cerr << "Error: cat expects 1 argument\n";
                return false;
            }
            
            return fs.cat(args[1]);
        }},
        {"ln", [&](const std::vector<std::string>& args) {
            if (args.size() != 3) {
                std::cerr << "Error: ln expects 2 arguments\n";
                return false;
            }
            
            return fs.ln(args[1], args[2]);
        }},
        {"chmod", [&](const std::vector<std::string>& args) {
            if (args.size() != 3) {
                std::cerr << "Error: chmod expects 2 arguments (mode, path)\n";
                return false;
            }
            
            unsigned int mode;
            try {
                mode = std::stoi(args[1], nullptr, 8);
            } 
            catch (const std::exception&) {
                std::cerr << "Error: Invalid mode '" << args[1] << "'; must be octal (e.g., 755)\n";
                return false;
            }
            
            return fs.chmod(args[2], mode);
        }},
        {"ls", [&](const std::vector<std::string>& args) {
            if (args.size() > 2) {
                std::cerr << "Error: ls expects 0 or 1 argument\n";
                return false;
            }
            
            fs.ls(args.size() == 1 ? "" : args[1]);
            return true;
        }},
        {"ll", [&](const std::vector<std::string>& args) {
            if (args.size() != 1) {
                std::cerr << "Error: ll expects no arguments\n";
                return false;
            }
            
            fs.ll();
            return true;
        }},
        {"pwd", [&](const std::vector<std::string>& args) {
            if (args.size() != 1) {
                std::cerr << "Error: pwd expects no arguments\n";
                return false;
            }
            
            fs.pwd();
            return true;
        }},
        {"echo", [&](const std::vector<std::string>& args) {
            if (args.size() < 2) {
                std::cerr << "Error: echo expects at least 1 argument\n";
                return false;
            }
            
            std::string text = args[1];
            std::string file, redirect;
            if (args.size() >= 4 && (args[2] == ">" || args[2] == ">>")) {
                redirect = args[2];
                file = args[3];
            } 
            else if (args.size() != 2) {
                std::cerr << "Error: echo expects text [> file | >> file]\n";
                return false;
            }
            
            fs.echo(text, file, redirect);
            return true;
        }},
        {"help", [&](const std::vector<std::string>& args) {
            if (args.size() != 1) {
                std::cerr << "Error: help expects no arguments\n";
                return false;
            }
            
            display_help();
            return true;
        }},
        {"exit", [&](const std::vector<std::string>& args) {
            if (args.size() != 1) {
                std::cerr << "Error: exit expects no arguments\n";
                return false;
            }
            
            return false;
        }}
    };

    auto it = commands.find(cmd);
    if (it == commands.end()) {
        std::cerr << "Error: Unknown command '" << cmd << "'. Type 'help' for available commands.\n";
        return true;
    }

    return it->second(tokens);
}

int main(int argc, char* argv[]) {
    FileSystem fs;

    if (argc > 1) {
        std::vector<std::string> tokens;
        for (int i = 1; i < argc; ++i) {
            tokens.emplace_back(argv[i]);
        }
        if (!process_command(fs, tokens)) {
            return 1;
        }
        return 0;
    }

    std::string input;
    while (true) {
        std::cout << std::filesystem::path(fs.pwd()).string() << "> ";
        std::getline(std::cin, input);
        if (std::cin.eof() || input.empty()) {
            continue;
        }

        std::vector<std::string> tokens = split(input);
        if (!process_command(fs, tokens)) {
            break;
        }
    }

    return 0;
}
