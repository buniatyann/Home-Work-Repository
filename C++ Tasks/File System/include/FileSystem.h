#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace fs = std::filesystem;

class FileSystem {
public:
    FileSystem() : cwd(fs::current_path()) {}
    ~FileSystem() = default;

    struct copy_opt_t {
        bool recursive = false;
        bool force = false;

        copy_opt_t() : recursive(false), force(false) {}
    };

    struct remove_opt_t {
        bool recursive = false;
        bool force = false;
        
        remove_opt_t() : recursive(false), force(false) {}
    };

    struct move_opt_t {
        bool force = false;
        
        move_opt_t() : force(false) {}
    };

    bool cd(const std::string& path);
    bool touch(const std::string& file);
    bool mkdir(const std::string& dir);
    bool rm(const std::string& path, const remove_opt_t& opts = remove_opt_t{});
    bool cp(const std::string& from, const std::string& to, const copy_opt_t& opts = copy_opt_t{});
    bool mv(const std::string& from, const std::string& to, const move_opt_t& opts = move_opt_t{});
    bool cat(const std::string& file);
    bool ln(const std::string& target, const std::string& link);
    bool chmod(const std::string& path, unsigned int mode);
    void ll() const;
    fs::path pwd() const;
    void ls(const std::string& path = "") const;
    void echo(const std::string& text, const std::string& file = "", const std::string& redirect = "") const;

private:
    fs::path cwd;

    bool exists_in_cwd(const fs::path& path) const {
        return fs::exists(cwd / path);
    }
};

#endif // FILE_SYSTEM