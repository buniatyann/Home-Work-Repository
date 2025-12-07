#ifndef DATA_LOADER_HPP
#define DATA_LOADER_HPP

#include <string>
#include <vector>

class DataLoader {
public:
    std::vector<std::string> load(const std::string& filePath);
};

#endif // DATA_LOADER_HPP
