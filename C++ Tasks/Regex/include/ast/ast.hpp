#ifndef REGEX_AST_H
#define REGEX_AST_H

#include <string>
#include <vector>
#include <memory>

enum class quantifier {
    none, asterisk, lazy_asterisk, plus, lazy_plus, optional, lazy_optional
};

struct pattern {
    virtual ~pattern() = default;
};

struct atomic_pattern : pattern {
    std::string char_;
    atomic_pattern(const std::string& c) : char_(c) {}
};

struct dot_pattern : pattern {};

struct character_class : pattern {
    std::string class_;
    character_class(const std::string& c) : class_(c) {}
};

struct complex_class : pattern {
    std::string name;
    bool negated;
    bool matches(const std::string& c) const {
        return false; // Placeholder
    }
    complex_class(const std::string& n, bool neg) : name(n), negated(neg) {}
};

struct caret_anchor : pattern {};
struct dollar_anchor : pattern {};

struct regex : pattern {
    std::vector<std::pair<std::string, std::shared_ptr<pattern>>> subpatterns;
    bool is_capturing;
    std::string group_name;
    regex(bool capturing = false, const std::string& name = "") 
        : is_capturing(capturing), group_name(name) {}
    bool is_capturing_group() const { return is_capturing; }
};

struct regex_alternative : pattern {
    std::vector<std::shared_ptr<regex>> alternatives;
    bool is_capturing;
    std::string group_name;
    regex_alternative(bool capturing = false, const std::string& name = "") 
        : is_capturing(capturing), group_name(name) {}
    bool is_capturing_group() const { return is_capturing; }
};

#endif // REGEX_AST_H