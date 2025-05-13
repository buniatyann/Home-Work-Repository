#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cctype>
#include <vector>
#include <set>
#include "token.hpp"

class lexer {
public:
    lexer() = default;
    std::vector<token> tokenize(const std::string& expression) const;

private:
    inline static const std::set<std::string> valid_functions = {
        "sqrt", "log2", "ln", "log10", "sin", "cos", "tan", "cot",
        "asin", "acos", "atan", "sinh", "cosh", "tanh"
    };
    
    inline static const std::set<std::string> valid_constants = {
        "pi", "e"
    };
};

#endif // LEXER_HPP