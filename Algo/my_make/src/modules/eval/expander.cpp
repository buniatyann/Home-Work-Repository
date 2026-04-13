#include "eval/expander.h"

namespace mymake {

Expander::Expander(VariableTable& vars) : vars_(vars) {}

std::string Expander::expand(const std::string& text) const {
    size_t pos = 0;
    return expand_impl(text, pos, '\0');
}

std::string Expander::expand_impl(const std::string& text, size_t& pos,
                                   char close_delim) const {
    std::string result;

    while (pos < text.size()) {
        char c = text[pos];

        // Stop if we hit the closing delimiter for a nested expansion.
        if (c == close_delim) {
            return result;
        }

        if (c == '$' && pos + 1 < text.size()) {
            pos++; // skip '$'

            if (text[pos] == '$') {
                // $$ -> literal $
                result += '$';
                pos++;
            } else {
                result += expand_ref(text, pos);
            }
            continue;
        }

        result += c;
        pos++;
    }

    return result;
}

std::string Expander::expand_ref(const std::string& text, size_t& pos) const {
    if (pos >= text.size()) {
        return {};
    }

    char c = text[pos];

    // $(name) or ${name}
    if (c == '(' || c == '{') {
        char open = c;
        char close = (open == '(') ? ')' : '}';
        pos++; // skip '(' or '{'

        // Recursively expand the content between delimiters.
        // This handles $($(VAR)) nested references.
        std::string name = expand_impl(text, pos, close);

        if (pos < text.size() && text[pos] == close) {
            pos++; // skip ')' or '}'
        }

        return resolve(name);
    }

    // Single-character variable: $@, $<, $^, $*, etc.
    pos++;
    return resolve(std::string(1, c));
}

std::string Expander::resolve(const std::string& name) const {
    // Guard against infinite recursion.
    if (expanding_.count(name)) {
        return {};
    }

    auto var = vars_.lookup_full(name);
    if (!var) {
        return {};
    }

    if (var->flavor == VarFlavor::Recursive) {
        // Recursive: expand the stored value now.
        expanding_.insert(name);
        std::string result = expand(var->value);
        expanding_.erase(name);
        return result;
    }

    // Simple: value was already expanded at assignment time.
    return var->value;
}

} // namespace mymake
