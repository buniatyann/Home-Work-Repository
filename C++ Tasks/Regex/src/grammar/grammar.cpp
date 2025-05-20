#include "../../include/grammar/grammar.hpp"
#include <stdexcept>

std::vector<regex_grammar::token> regex_grammar::tokenize(const std::string& pattern) const {
    std::vector<token> tokens;
    for (size_t i = 0; i < pattern.length(); ++i) {
        char c = pattern[i];
        if (is_special_char(c)) {
            switch (c) {
                case '*': 
                    tokens.push_back({token::type::star, "*"}); 
                    break;
                case '+': 
                    tokens.push_back({token::type::plus, "+"}); 
                    break;
                case '|': 
                    tokens.push_back({token::type::or_, "|"}); 
                    break;
                case '.': 
                    tokens.push_back({token::type::dot, "."}); 
                    break;
                case '(': 
                    tokens.push_back({token::type::lparen, "("}); 
                    break;
                case ')': 
                    tokens.push_back({token::type::rparen, ")"});   
                    break;
                case '?': 
                    tokens.push_back({token::type::question, "?"}); 
                    break;
                case '^': 
                    tokens.push_back({token::type::caret, "^"}); 
                    break;
                case '$': 
                    tokens.push_back({token::type::dollar, "$"}); 
                    break;
                default: 
                    throw std::runtime_error("Invalid special character");
            }
        } 
        else if (c == '\\') {
            if (i + 1 < pattern.length()) {
                char next = pattern[++i];
                if (next == 'd' || next == 'D' || next == 'w' || next == 'W' || next == 's' || next == 'S') {
                    tokens.push_back({token::type::class_, "\\" + std::string(1, next)});
                } 
                else {
                    tokens.push_back({token::type::char_, std::string(1, next)});
                }
            } 
            else {
                throw std::runtime_error("Invalid escape sequence");
            }
        } 
        else {
            tokens.push_back({token::type::char_, std::string(1, c)});
        }
    }

    tokens.push_back({token::type::end, ""});
    return tokens;
}

bool regex_grammar::is_special_char(char c) const {
    return c == '*' || c == '+' || c == '|' || c == '.' || c == '(' || c == ')' || c == '?' || c == '^' || c == '$';
}

std::shared_ptr<pattern> regex_grammar::parse(const std::string& pattern) const {
    auto tokens = tokenize(pattern);
    size_t pos = 0;
    auto result = parse_pattern(tokens, pos);
    if (pos < tokens.size() && tokens[pos].type_ != token::type::end) {
        throw std::runtime_error("Unexpected token at end of pattern");
    }
    
    return result;
}

std::shared_ptr<pattern> regex_grammar::parse_pattern(const std::vector<token>& tokens, size_t& pos) const {
    return parse_alternative(tokens, pos);
}

std::shared_ptr<pattern> regex_grammar::parse_alternative(const std::vector<token>& tokens, size_t& pos) const {
    auto regex = parse_regex(tokens, pos);
    if (pos < tokens.size() && tokens[pos].type_ == token::type::or_) {
        auto alternative = std::make_shared<regex_alternative>();
        alternative->alternatives.push_back(std::dynamic_pointer_cast<regex>(regex));
        while (pos < tokens.size() && tokens[pos].type_ == token::type::or_) {
            ++pos;
            alternative->alternatives.push_back(std::dynamic_pointer_cast<regex>(parse_regex(tokens, pos)));
        }
        
        return alternative;
    }
    
    return regex;
}

std::shared_ptr<pattern> regex_grammar::parse_regex(const std::vector<token>& tokens, size_t& pos) const {
    auto regex = std::make_shared<regex>();
    while (pos < tokens.size() && tokens[pos].type_ != token::type::end && tokens[pos].type_ != token::type::or_ && tokens[pos].type_ != token::type::rparen) {
        auto atom = parse_atom(tokens, pos);
        std::string quantifier = "";
        if (pos < tokens.size()) {
            if (tokens[pos].type_ == token::type::star) {
                quantifier = (pos + 1 < tokens.size() && tokens[pos + 1].type_ == token::type::question) ? "*?" : "*";
                pos += (quantifier == "*?") ? 2 : 1;
            } 
            else if (tokens[pos].type_ == token::type::plus) {
                quantifier = (pos + 1 < tokens.size() && tokens[pos + 1].type_ == token::type::question) ? "+?" : "+";
                pos += (quantifier == "+?") ? 2 : 1;
            } 
            else if (tokens[pos].type_ == token::type::question) {
                quantifier = (pos + 1 < tokens.size() && tokens[pos + 1].type_ == token::type::question) ? "??" : "?";
                pos += (quantifier == "??") ? 2 : 1;
            }
        }
        
        regex->subpatterns.emplace_back(quantifier, atom);
    }
    
    return regex;
}

std::shared_ptr<pattern> regex_grammar::parse_atom(const std::vector<token>& tokens, size_t& pos) const {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Unexpected end of pattern");
    }
    
    auto& token = tokens[pos];
    ++pos;
    switch (token.type_) {
        case token::type::char_:
            return std::make_shared<atomic_pattern>(token.value);
        case token::type::dot:
            return std::make_shared<dot_pattern>();
        case token::type::class_:
            return std::make_shared<character_class>(token.value);
        case token::type::caret:
            return std::make_shared<caret_anchor>();
        case token::type::dollar:
            return std::make_shared<dollar_anchor>();
        case token::type::lparen: {
            bool capturing = true; // Simplified; assume capturing
            auto regex = parse_pattern(tokens, pos);
            if (pos >= tokens.size() || tokens[pos].type_ != token::type::rparen) {
                throw std::runtime_error("Expected closing parenthesis");
            }
    
            ++pos;
            auto regex_ptr = std::dynamic_pointer_cast<regex>(regex);
            if (!regex_ptr) {
                regex_ptr = std::make_shared<regex>();
                regex_ptr->subpatterns.emplace_back("", regex);
            }
    
            regex_ptr->is_capturing = capturing;
            return regex_ptr;
        }
        default:
            throw std::runtime_error("Invalid token in atom: " + token.value);
    }
}
