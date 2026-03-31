#ifndef MYMAKE_EXECUTOR_EXECUTOR_H
#define MYMAKE_EXECUTOR_EXECUTOR_H

#include "graph/graph.h"
#include "variables/variable_table.h"
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>

namespace mymake {

struct Config; // forward declare

class Executor {
public:
    Executor(const Config& config, VariableTable& vars);

    // Execute the dependency graph. Returns 0 on success, non-zero on failure.
    int execute(const DependencyGraph& graph,
                const std::vector<std::string>& goals);

private:
    bool needs_rebuild(const GraphNode& node) const;
    int run_recipes(const GraphNode& node);
    int run_command(const std::string& command, bool silent, bool ignore_error);

    std::optional<std::filesystem::file_time_type>
        get_mtime(const std::string& path) const;

    mutable std::unordered_map<std::string,
        std::optional<std::filesystem::file_time_type>> mtime_cache_;

    const Config& config_;
    VariableTable& vars_;
};

} // namespace mymake

#endif // MYMAKE_EXECUTOR_EXECUTOR_H
