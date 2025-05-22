#include "../include/FileSystem.h"
#include <fstream>

bool FileSystem::cd(const std::string& path) {
    try {
        fs::path new_cwd;
        if (path.empty()) {
            new_cwd = cwd.root_path(); // / on Linux, C:\ on Windows
        } 
        else {
            fs::path target = path;
            if (!target.is_absolute()) {
                target = cwd / path; // Resolve relative to cwd
            }
            
            new_cwd = fs::canonical(target); // Resolve .., ., symlinks
        }

        if (!fs::exists(new_cwd)) {
            std::cerr << "Error: Directory '" << path << "' does not exist\n";
            return false;
        }
        
        if (!fs::is_directory(new_cwd)) {
            std::cerr << "Error: '" << path << "' is not a directory\n";
            return false;
        }

        cwd = new_cwd;
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot change to '" << path << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue changing to '" << path << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::touch(const std::string& file) {
    if (file.empty()) {
        std::cerr << "Error: touch requires a non-empty file name\n";
        return false;
    }

    try {
        fs::path path_obj = cwd / file;
        if (fs::exists(path_obj)) {
            fs::last_write_time(path_obj, fs::file_time_type::clock::now());
            // std::cout << "Updated timestamp: '" << path_obj << "'\n";
            return true;
        }

        std::ofstream ofs(path_obj);
        if (!ofs) {
            std::cerr << "Error: Cannot create file '" << file << "': Unable to write\n";
            return false;
        }

        ofs.close();
        // std::cout << "Created: '" << path_obj << "'\n";
        
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot touch '" << file << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue with touch '" << file << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::mkdir(const std::string& dir) {
    if (dir.empty()) {
        std::cerr << "Error: mkdir requires a non-empty directory name\n";
        return false;
    }

    try {
        fs::path path_obj = cwd / dir;
        if (fs::exists(path_obj)) {
            std::cerr << "Error: Directory or file '" << dir << "' already exists\n";
            return false;
        }

        fs::create_directory(path_obj);
        // std::cout << "Created directory: '" << path_obj << "'\n";
        
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot create directory '" << dir << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue creating directory '" << dir << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::rm(const std::string& rhs, const remove_opt_t& opts) {
    if (rhs.empty()) {
        std::cerr << "Error: rm requires a non-empty file or directory path\n";
        return false;
    }

    try {
        fs::path path_obj = cwd / rhs;
        if (!fs::exists(path_obj)) {
            if (opts.force) {
                return true; // Ignore non-existent with -f
            }
        
            std::cerr << "Error: Cannot remove '" << path_obj << "': No such file or directory\n";
            return false;
        }

        if (fs::is_directory(path_obj) && !opts.recursive) {
            std::cerr << "Error: '" << path_obj << "' is a directory; use -r to remove recursively\n";
            return false;
        }

        if (fs::is_directory(path_obj)) {
            fs::remove_all(path_obj);
        } 
        else {
            fs::remove(path_obj);
        }

        // std::cout << "Removed: '" << path_obj << "'\n";
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot remove '" << rhs << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue removing '" << rhs << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::cp(const std::string& src, const std::string& dst, const copy_opt_t& opts) {
    if (src.empty() || dst.empty()) {
        std::cerr << "Error: cp requires non-empty source and destination paths\n";
        return false;
    }

    try {
        fs::path src_path = cwd / src;
        fs::path dst_path = cwd / dst;

        if (!fs::exists(src_path)) {
            std::cerr << "Error: Cannot copy '" << src << "': No such file or directory\n";
            return false;
        }

        if (!opts.force && fs::equivalent(src_path, dst_path)) {
            std::cerr << "Error: Source and destination are the same: '" << src << "'\n";
            return false;
        }

        if (fs::exists(dst_path) && fs::is_directory(dst_path)) {
            dst_path = dst_path / src_path.filename();
        }

        if (fs::is_directory(src_path) && !opts.recursive) {
            std::cerr << "Error: '" << src << "' is a directory; use -r to copy recursively\n";
            return false;
        }

        if (fs::is_directory(src_path)) {
            fs::copy(src_path, dst_path, opts.force ? fs::copy_options::recursive | fs::copy_options::overwrite_existing : fs::copy_options::recursive);
        } 
        else {
            fs::copy(src_path, dst_path, opts.force ? fs::copy_options::overwrite_existing : fs::copy_options::none);
        }

        // std::cout << "Copied: '" << src_path << "' to '" << dst_path << "'\n";
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot copy '" << src << "' to '" << dst << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue copying '" << src << "' to '" << dst << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::mv(const std::string& src, const std::string& dst, const move_opt_t& opts) {
    if (src.empty() || dst.empty()) {
        std::cerr << "Error: mv requires non-empty source and destination paths\n";
        return false;
    }

    try {
        fs::path src_path = cwd / src;
        fs::path dst_path = cwd / dst;

        if (!fs::exists(src_path)) {
            std::cerr << "Error: Cannot move '" << src << "': No such file or directory\n";
            return false;
        }

        if (!opts.force && fs::equivalent(src_path, dst_path)) {
            std::cerr << "Error: Source and destination are the same: '" << src << "'\n";
            return false;
        }

        if (fs::exists(dst_path) && fs::is_directory(dst_path)) {
            dst_path = dst_path / src_path.filename();
        }

        if (opts.force && fs::exists(dst_path)) {
            if (fs::is_directory(dst_path)) {
                fs::remove_all(dst_path);
            } 
            else {
                fs::remove(dst_path);
            }
        }

        fs::rename(src_path, dst_path);
        // std::cout << "Moved: '" << src_path << "' to '" << dst_path << "'\n";
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot move '" << src << "' to '" << dst << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue moving '" << src << "' to '" << dst << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::cat(const std::string& file) {
    if (file.empty()) {
        std::cerr << "Error: cat requires a non-empty file name\n";
        return false;
    }

    try {
        fs::path path_obj = cwd / file;
        if (!fs::exists(path_obj)) {
            std::cerr << "Error: Cannot read '" << file << "': No such file or directory\n";
            return false;
        }
        
        if (!fs::is_regular_file(path_obj)) {
            std::cerr << "Error: '" << file << "' is not a regular file\n";
            return false;
        }

        std::ifstream ifs(path_obj);
        if (!ifs) {
            std::cerr << "Error: Cannot open '" << file << "' for reading\n";
            return false;
        }

        std::cout << ifs.rdbuf();
        ifs.close();
        
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot read '" << file << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue reading '" << file << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::ln(const std::string& target, const std::string& link) {
    if (target.empty() || link.empty()) {
        std::cerr << "Error: ln requires non-empty target and link paths\n";
        return false;
    }

    try {
        fs::path target_path = cwd / target;
        fs::path link_path = cwd / link;

        if (!fs::exists(target_path)) {
            std::cerr << "Error: Cannot create link to '" << target << "': No such file or directory\n";
            return false;
        }

        if (fs::exists(link_path)) {
            std::cerr << "Error: Link path '" << link << "' already exists\n";
            return false;
        }

        fs::create_symlink(target_path, link_path);
        // std::cout << "Created symlink: '" << link_path << "' -> '" << target_path << "'\n";
        
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot create symlink '" << link << "' to '" << target << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue creating symlink '" << link << "': " << e.what() << "\n";
        return false;
    }
}

bool FileSystem::chmod(const std::string& path, unsigned int mode) {
    if (path.empty()) {
        std::cerr << "Error: chmod requires a non-empty path\n";
        return false;
    }
    
    if (mode > 0777) {
        std::cerr << "Error: Invalid mode '" << mode << "'; must be 0-777\n";
        return false;
    }

    try {
        fs::path path_obj = cwd / path;
        if (!fs::exists(path_obj)) {
            std::cerr << "Error: Cannot chmod '" << path << "': No such file or directory\n";
            return false;
        }

        fs::perms perms = fs::perms::none;
        if (mode & 0400) {
            perms |= fs::perms::owner_read;
        }
        if (mode & 0200) {
            perms |= fs::perms::owner_write;
        }
        if (mode & 0100) { 
            perms |= fs::perms::owner_exec;
        }
        if (mode & 0040) {
            perms |= fs::perms::group_read;
        }
        if (mode & 0020) {
            perms |= fs::perms::group_write;
        }
        if (mode & 0010) {
            perms |= fs::perms::group_exec;
        }
        if (mode & 0004) {
            perms |= fs::perms::others_read;
        }
        if (mode & 0002) {
            perms |= fs::perms::others_write;
        }
        if (mode & 0001) {
            perms |= fs::perms::others_exec;
        }

        fs::permissions(path_obj, perms, fs::perm_options::replace);
        // std::cout << "Changed permissions: '" << path_obj << "' to " << std::oct << mode << std::dec << "\n";
        
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot chmod '" << path << "': " << e.what() << "\n";
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue with chmod '" << path << "': " << e.what() << "\n";
        return false;
    }
}

void FileSystem::ll() const {
    try {
        std::cout << "Directory contents of '" << cwd << "':\n";
        for (const auto& entry : fs::directory_iterator(cwd)) {
            auto path = entry.path();
            auto status = fs::status(path);
            auto time = fs::last_write_time(path);
            auto time_point = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                time - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
            auto ctime = std::chrono::system_clock::to_time_t(time_point);

            std::string perms = fs::is_directory(path) ? "d" : "-";
            perms += (status.permissions() & fs::perms::owner_read) != fs::perms::none ? "r" : "-";
            perms += (status.permissions() & fs::perms::owner_write) != fs::perms::none ? "w" : "-";
            perms += (status.permissions() & fs::perms::owner_exec) != fs::perms::none ? "x" : "-";
            perms += (status.permissions() & fs::perms::group_read) != fs::perms::none ? "r" : "-";
            perms += (status.permissions() & fs::perms::group_write) != fs::perms::none ? "w" : "-";
            perms += (status.permissions() & fs::perms::group_exec) != fs::perms::none ? "x" : "-";
            perms += (status.permissions() & fs::perms::others_read) != fs::perms::none ? "r" : "-";
            perms += (status.permissions() & fs::perms::others_write) != fs::perms::none ? "w" : "-";
            perms += (status.permissions() & fs::perms::others_exec) != fs::perms::none ? "x" : "-";

            uint64_t size = fs::is_regular_file(path) ? fs::file_size(path) : 0;
            std::cout << perms << " " << std::setw(10) << size << " "
                      << std::put_time(std::localtime(&ctime), "%Y-%m-%d %H:%M:%S") << " "
                      << path.filename().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot list directory '" << cwd << "': " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue listing directory: " << e.what() << "\n";
    }
}

fs::path FileSystem::pwd() const {
    try {
        return cwd;
    } catch (const std::exception& e) {
        std::cerr << "Error: Cannot display current directory: " << e.what() << "\n";
        return fs::path();
    }
}

void FileSystem::ls(const std::string& path) const {
    try {
        fs::path dir_path = path.empty() ? cwd : cwd / path;
        if (!fs::exists(dir_path)) {
            std::cerr << "Error: Directory '" << path << "' does not exist\n";
            return;
        }
        
        if (!fs::is_directory(dir_path)) {
            std::cerr << "Error: '" << path << "' is not a directory\n";
            return;
        }

        // std::cout << "Contents of '" << dir_path << "':\n";
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            std::cout << entry.path().filename().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot list directory '" << path << "': " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue listing directory '" << path << "': " << e.what() << "\n";
    }
}

void FileSystem::echo(const std::string& text, const std::string& file, const std::string& redirect) const {
    try {
        if (file.empty()) {
            std::cout << text << "\n";
            return;
        }

        fs::path file_path = cwd / file;
        std::ofstream ofs;
        if (redirect == ">>") {
            ofs.open(file_path, std::ios::app);
        } 
        else {
            ofs.open(file_path);
        }

        if (!ofs) {
            std::cerr << "Error: Cannot write to '" << file << "'\n";
            return;
        }

        ofs << text << "\n";
        ofs.close();
        // std::cout << "Wrote to '" << file_path << "'\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot write to '" << file << "': " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue writing to '" << file << "': " << e.what() << "\n";
    }
}