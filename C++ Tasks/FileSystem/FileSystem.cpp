#include "FileSystem.h"

void FileSystem::cd(const std::string &rhs)
{
    if(rhs.empty()) {
        cwd = cwd.root_directory();
    }
    else {
        std::vector<std::string> paths;
        std::string members {};
        for(const char c : rhs){
            if(c != '/') {
                paths.push_back(members);
                members.clear();
            }
            else {
                paths.emplace_back(c);
            }
        }

        change_directory(paths);
    }
}

void FileSystem::cd(const char *rhs)
{
    if(rhs =='\0') {
        cwd = cwd.root_directory();
    }
    else {
        std::vector<std::string> paths;
        std::string members {};
        for(int i = 0; *(rhs + i) != '/0'; ++i) {
            if(*(rhs + i) != '/') {
                paths.push_back(members);
                members.clear();
            }
            else {
                paths.emplace_back(*(rhs + i));
            }
        }
    }
}

void FileSystem::touch(const std::string &rhs)
{
    if(rhs.empty()) {
        std::cerr << "Not proper use of touch function" << std::endl; 
    }
    else {
        fs::path path_obj(rhs);
        if(exists_in_cwd(path_obj)) {
            std::cout << "Your given file already exists" << std::endl;
            return;
        }
        else {
            std::ofstream(path_obj);
            return;
        }

        auto now = fs::file_time_type::clock::now();
        fs::last_write_time(path_obj, now);
    }
}

void FileSystem::touch(const char *rhs)
{
    if(rhs == '\0') {
        std::cerr << "Not proper use of touch function \n" << "Must pass a file name";
    }
    
    fs::path path_obj(rhs);
    if(exists_in_cwd(path_obj)) {
        std::cout << "Your given file already exists" << std::endl;
        return;
    }
    else {
        std::ofstream(path_obj);
    }

    auto now = fs::file_time_type::clock::now();
    fs::last_write_time(path_obj, now);
  
}

void FileSystem::mkdir(const std::string &rhs)
{
    if (rhs.empty()) {
        std::cerr << "Not proper use of mkdir function \n" << "Must pass a file name";
        return;
    }
    
    fs::path path_obj(rhs);
    if(exists_in_cwd(path_obj)){
        std::cout << "Name with that directory already exists in file system" << std::endl;
        return;
    }

    fs::create_directory(path_obj);
    auto now = fs::file_time_type::clock::now();
    fs::last_write_time(rhs, now);
}

void FileSystem::mkdir(const char* rhs)
{
    if (rhs == nullptr || std::string(rhs).empty()) {
        std::cerr << "Not proper use of mkdir function \n" << "Must pass a file name";
        return;
    }

    std::string dir_name(rhs);
    fs::path path_obj(dir_name);
    if(exists_in_cwd(path_obj)){
        std::cout << "Name with that directory already exists in file system" << std::endl;
        return;
    }

    fs::create_directory(dir_name);
    auto now = fs::file_time_type::clock::now();
    fs::last_write_time(dir_name, now);
}

void FileSystem::rm(const std::string &rhs)
{
    // if (rhs.empty()) {
    //     std::cerr << "Not proper use of rm function \n" << "Must pass a file name";
    //     return;
    // }

    // fs::path path_obj(rhs);
    // if(!exists_in_cwd(path_obj)){
    //     std::cout << "rm cannot remove object that has not any name" << std::endl;
    //     return;
    // }

    // try {
    //     if (fs::is_directory(path_obj)) {
    //         fs::remove_all(path_obj); // for directories
    //     } 
    //     else {
    //         fs::remove(path_obj); // for files
    //     }
        
    //     std::cout << "Removed: " << path_obj << "\n";
    // } catch (const fs::filesystem_error& e) {
    //     std::cerr << "Error: " << e.what() << "\n";
    // }

    if(rhs.empty()){
        std::cerr << "Error: rm requires non-empty file or directory path \n";
        // return false;
    }

    try {
        fs::path path_obj = fs::current_path() / rhs;
        if(!fs::exists(path_obj)) {
            std::cerr << "Error: Cannot remove " << path_obj << " : No such file or directory \n";
            // return true;
        }

        if(fs::is_directory(path_obj)) {
            fs::remove_all(path_obj);
        }
        else {
            fs::remove(path_obj);
        }

        // return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot remove: " << rhs << ": " << e.what() << "\n";
        // return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue removing '" << rhs << "': " << e.what() << "\n";
        // return false;
    } catch (...) {
        std::cerr << "Error: Unknown error removing '" << rhs << "'\n";
        // return false;
    }
}

void FileSystem::rm(const char* rhs)
{
    if(rhs == nullptr || std::string(rhs).empty()){
        std::cerr << "Error: rm requires non-empty file or directory path \n";
        // return false;
    }

    try {
        fs::path path_obj = fs::current_path() / rhs;
        if(!fs::exists(path_obj)) {
            std::cerr << "Error: Cannot remove " << path_obj << " : No such file or directory \n";
            // return true;
        }

        if(fs::is_directory(path_obj)) {
            fs::remove_all(path_obj);
        }
        else {
            fs::remove(path_obj);
        }

        // return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot remove: " << rhs << ": " << e.what() << "\n";
        // return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue removing '" << rhs << "': " << e.what() << "\n";
        // return false;
    } catch (...) {
        std::cerr << "Error: Unknown error removing '" << rhs << "'\n";
        // return false;
    }
}

void FileSystem::ll() const
{
    // TODO
}

void FileSystem::cp(const std::string &from, const std::string &to)
{
    if(from.empty() or to.empty()) {
        std::cerr << "Error: cp requires non-empty source and destination paths\n";
    }

    try {
        fs::path source_path = fs::current_path() / from;
        fs::path destination_path = fs::current_path() / to;

        if(!fs::exists(source_path)) {
            std::cerr << "Error: Cannot copy '" << from << "': No such file or directory";
            // return false;
        }

        if(fs::equivalent(source_path, destination_path)) {
            std::cerr << "Error: Source and destination are the same: '" << from << "'\n";
            //return false;
        }

        if(fs::exists(destination_path) && fs::is_directory(destination_path)) {
            destination_path = destination_path / source_path.filename();
        }

        if(fs::is_directory(source_path)) {
            fs::copy(source_path, destination_path, fs::copy_options::recursive); // ?
        }
        else {
            fs::copy(source_path, destination_path, fs::copy_options::overwrite_existing);
        }

        // return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot copy '" << from << "' to '" << to << "': " << e.what() << "\n";
        // return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue copying '" << from << "' to '" << to << "': " << e.what() << "\n";
        // return false;
    } catch (...) {
        std::cerr << "Error: Unknown error copying '" << from << "' to '" << to << "'\n";
        // return false;
    }
}

void FileSystem::cp(const char* from, const char* to)
{
    if (from == nullptr || to == nullptr || std::string(from).empty() || std::string(to).empty()) {
        std::cerr << "Error: cp requires non-empty source and destination paths\n";
        return;
    }

    try {
        fs::path source_path = fs::current_path() / from;
        fs::path destination_path = fs::current_path() / to;

        if (!fs::exists(source_path)) {
            std::cerr << "Error: Cannot copy '" << from << "': No such file or directory";
            return;
        }

        if (fs::equivalent(source_path, destination_path)) {
            std::cerr << "Error: Source and destination are the same: '" << from << "'\n";
            return;
        }

        if (fs::exists(destination_path) && fs::is_directory(destination_path)) {
            destination_path = destination_path / source_path.filename();
        }

        if (fs::is_directory(source_path)) {
            fs::copy(source_path, destination_path, fs::copy_options::recursive);
        } else {
            fs::copy(source_path, destination_path, fs::copy_options::overwrite_existing);
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: Cannot copy '" << from << "' to '" << to << "': " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: Unexpected issue copying '" << from << "' to '" << to << "': " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Error: Unknown error copying '" << from << "' to '" << to << "'\n";
    }
}
