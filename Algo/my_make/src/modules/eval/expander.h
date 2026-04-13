#ifndef MYMAKE_EVAL_EXPANDER_H
#define MYMAKE_EVAL_EXPANDER_H

#include "eval/variable_table.h"
#include <string>
#include <unordered_set>

namespace mymake {

class Expander {
public:
    explicit Expander(VariableTable& vars);

    // Expand all $(VAR) / ${VAR} / $X references in text.
    std::string expand(const std::string& text) const;

private:
    // Recursive-descent expansion. Advances pos past consumed input.
    std::string expand_impl(const std::string& text, size_t& pos,
                            char close_delim) const;

    // Expand a single variable reference after '$'. Advances pos.
    std::string expand_ref(const std::string& text, size_t& pos) const;

    // Look up variable name, expand recursively if flavor is Recursive.
    std::string resolve(const std::string& name) const;

    VariableTable& vars_;

    // Guard against infinite recursion (e.g. A = $(A)).
    mutable std::unordered_set<std::string> expanding_;
};

} // namespace mymake

#endif // MYMAKE_EVAL_EXPANDER_H
