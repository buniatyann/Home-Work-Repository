#ifndef MYMAKE_CLI_CLI_H
#define MYMAKE_CLI_CLI_H

#include <string>
#include <unordered_map>
#include <vector>

namespace mymake {

struct Config {
    std::string makefile_path;
    std::vector<std::string> goals;
    std::unordered_map<std::string, std::string> overrides;
    int jobs = 1;
    bool dry_run = false;
    bool always_make = false;
    bool keep_going = false;
    bool silent = false;
    std::string directory;
    bool debug = false;
};

// Parse command-line arguments into a Config.
// Returns the Config on success, or prints usage and exits on error.
Config parse_args(int argc, char* argv[]);

} // namespace mymake

#endif // MYMAKE_CLI_CLI_H
