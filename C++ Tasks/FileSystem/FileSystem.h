#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <chrono>

namespace fs = std::filesystem;

class FileSystem {
public:
    FileSystem() = default;
    ~FileSystem() = default;


    void cd(const std::string& rhs);
    void cd(const char* rhs);

    void touch(const std::string& rhs);
    void touch(const char* rhs);
    
    void mkdir(const std::string& rhs);
    void mkdir(const char* rhs);

    void rm(const std::string& rhs);
    void rm(const char* rhs);

    void ll() const;
    void cp(const std::string& from, const std::string& to);
    void cp(const char* from, const char* to);

private:
    // struct Directory {
    //     std::unordered_map<std::string, Directory*> internals_;
    //     std::string dir_name_;
    // };

    // Directory* root_;
    // Directory* cwd_;
    // std::string cwd_path_;
    fs::path cwd;
    // bool os_mode_;

    void change_directory(const std::vector<std::string>& path);
    
    bool exists_in_cwd(const fs::path& path) {
        fs::path full_path = cwd / path;
        return fs::exists(full_path);
    }
};

#endif // FILE_SYSTEM