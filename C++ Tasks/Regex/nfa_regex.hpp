#ifndef NFA_REGEX_H
#define NFA_REGEX_H

#include "engine_nfa.hpp"
#include "match.hpp"
#include "grammar.hpp"
#include "conversion_builder.hpp"
#include <memory>

class nfa_regex {
public:
    nfa_regex(const std::string& regex, bool iterative = true);
    std::unique_ptr<match> find_first_match(const std::string& string) const;
    std::vector<std::unique_ptr<match>> find_all_matches(const std::string& string) const;

private:
    std::string source_;
    std::unique_ptr<engine_nfa> nfa_;
    bool iterative_;
    nfa_result compute(const std::string& string, size_t i) const;
};

#endif // NFA_REGEX_H