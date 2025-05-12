#include "nfa_regex.hpp"
#include <memory>

nfa_regex::nfa_regex(const std::string& regex, bool iterative) : source_(regex), iterative_(iterative) {
    regex_grammar grammar;
    auto ast = grammar.parse(regex);
    conversion_builder cb([]() { return std::make_unique<engine_nfa>(); });
    nfa_ = cb.regex_to_nfa(ast);
}

nfa_result nfa_regex::compute(const std::string& string, size_t i) const {
    return iterative_ ? nfa_->iterative_compute(string, i) : nfa_->compute(string, i);
}

std::unique_ptr<match> nfa_regex::find_first_match(const std::string& string) const {
    for (size_t i = 0; i < string.length(); ++i) {
        auto r = compute(string.substr(i), i);
        if (r.success) {
            auto match_ptr = std::make_unique<match>(match::from_nfa_result(string, i, r));
            if (match_ptr->start() != match_ptr->end()) {
                return match_ptr;
            }
        }
    }
 
    return nullptr;
}

std::vector<std::unique_ptr<match>> nfa_regex::find_all_matches(const std::string& string) const {
    std::vector<std::unique_ptr<match>> matches;
    for (size_t i = 0; i < string.length(); ++i) {
        auto r = compute(string.substr(i), i);
        if (r.success) {
            auto match_ptr = std::make_unique<match>(match::from_nfa_result(string, i, r));
            if (match_ptr->start() != match_ptr->end()) {
                matches.push_back(std::move(match_ptr));
                if (r.ending_position != i) {
                    i = r.ending_position - 1;
                }
            }
        }
    }
 
    return matches;
}