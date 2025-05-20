#include "../../include/matchers/matchers.hpp"

character_matcher::character_matcher(const std::string& c) : c_(c) {}

bool character_matcher::matches(const std::string& char_, size_t i) const {
    return c_ == char_;
}

std::string character_matcher::label() const {
    if (c_ == "EPSILON") {
        return "ε";
    }
    if (c_ == ".") {
        return "\\.";
    }
    
    return c_;
}

bool start_of_input_matcher::matches(const std::string& char_, size_t i) const {
    return char_ == "EPSILON" && i == 0;
}

std::string start_of_input_matcher::label() const {
    return "^";
}

bool end_of_input_matcher::matches(const std::string& char_, size_t i) const {
    return char_.empty();
}

std::string end_of_input_matcher::label() const {
    return "$";
}

bool dot_matcher::matches(const std::string& char_, size_t i) const {
    return !char_.empty() && char_ != "EPSILON" && char_ != "\n" && char_ != "\r";
}

std::string dot_matcher::label() const {
    return ".";
}

negated_matcher::negated_matcher(std::function<bool(const std::string&)> lambda, const std::string& name)
    : lambda_(lambda), name_(name) {}

bool negated_matcher::matches(const std::string& char_, size_t i) const {
    return !char_.empty() && char_ != "\n" && char_ != "\r" && char_ != "EPSILON" && lambda_(char_);
}

std::string negated_matcher::label() const {
    return name_;
}

positive_matcher::positive_matcher(std::function<bool(const std::string&)> lambda, const std::string& name)
    : lambda_(lambda), name_(name) {}

bool positive_matcher::matches(const std::string& char_, size_t i) const {
    return char_ != "EPSILON" && lambda_(char_);
}

std::string positive_matcher::label() const {
    return name_;
}