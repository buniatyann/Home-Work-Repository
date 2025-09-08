#include "include/regex/regex.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    try {
        // Test cases: {pattern, input, expected match}
        std::vector<std::tuple<std::string, std::string, bool>> tests = {
            {"a(b|c)*d", "abcd", true},
            {"^abc$", "abc", true},
            {"^abc$", "abcd", false},
            {"[0-9]+", "123", true},
            {"[^a-z][0-9]+$", "A123", true},
            {"(a|b)*c", "aabbc", true},
            {"a+", "aaa", true},
            {"", "", true},
            {"[a-", "a", false} // Invalid pattern, should throw
        };

        // Run tests for both NFA and DFA engines
        for (const auto& [pattern, input, expected] : tests) {
            std::cout << "Testing pattern: \"" << pattern << "\", input: \"" << input << "\"" << std::endl;

            // Test NFA
            try {
                regex::regex nfa_regex(pattern, regex::engine::nfa);
                auto result = nfa_regex.match(input);
                bool matched = result.is_matched();
                std::cout << "  NFA: " << (matched ? "Matched" : "No match")
                          << " (positions: " << result.get_start() << ", " << result.get_end() << ")"
                          << (matched == expected ? " [PASS]" : " [FAIL]") << std::endl;
            } catch (const regex::regex_error& e) {
                std::cout << "  NFA: Error: " << e.what() << " at position " << (expected ? " [FAIL]" : " [PASS]") << std::endl;
            }

            // Test DFA
            try {
                regex::regex dfa_regex(pattern, regex::engine::dfa);
                auto result = dfa_regex.match(input);
                bool matched = result.is_matched();
                std::cout << "  DFA: " << (matched ? "Matched" : "No match")
                          << " (positions: " << result.get_start() << ", " << result.get_end() << ")"
                          << (matched == expected ? " [PASS]" : " [FAIL]") << std::endl;
            } catch (const regex::regex_error& e) {
                std::cout << "  DFA: Error: " << e.what() << (expected ? " [FAIL]" : " [PASS]") << std::endl;
            }
        }

        // Optional: Command-line testing
        if (argc >= 3) {
            std::string pattern = argv[1];
            std::string input = argv[2];
            regex::engine eng = (argc >= 4 && std::string(argv[3]) == "--dfa") ? regex::engine::dfa : regex::engine::nfa;

            std::cout << "\nCommand-line test: pattern: \"" << pattern << "\", input: \"" << input << "\"" << std::endl;
            regex::regex regex(pattern, eng);
            auto result = regex.match(input);
            std::cout << (eng == regex::engine::nfa ? "NFA" : "DFA") << ": "
                      << (result.is_matched() ? "Matched" : "No match")
                      << " (positions: " << result.get_start() << ", " << result.get_end() << ")" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}