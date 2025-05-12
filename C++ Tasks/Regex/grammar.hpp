#ifndef REGEX_GRAMMAR_H
#define REGEX_GRAMMAR_H

#include "ast.hpp"
#include <string>
#include <vector>
#include <memory>

class regex_grammar {
public:
    std::shared_ptr<pattern> parse(const std::string& pattern) const;

private:
    struct token {
        enum class type { char_, star, plus, or_, dot, lparen, rparen, question, caret, dollar, class_, end };
        type type_;
        std::string value;
    };
    
    std::vector<token> tokenize(const std::string& pattern) const;
    std::shared_ptr<pattern> parse_pattern(const std::vector<token>& tokens, size_t& pos) const;
    std::shared_ptr<pattern> parse_alternative(const std::vector<token>& tokens, size_t& pos) const;
    std::shared_ptr<pattern> parse_regex(const std::vector<token>& tokens, size_t& pos) const;
    std::shared_ptr<pattern> parse_atom(const std::vector<token>& tokens, size_t& pos) const;
    bool is_special_char(char c) const;
};

#endif // REGEX_GRAMMAR_H