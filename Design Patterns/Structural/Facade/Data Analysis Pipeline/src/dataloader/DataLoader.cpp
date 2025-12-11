#include "../../include/dataloader/DataLoader.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> DataLoader::load(const std::string& filePath) {
    std::vector<std::string> data;
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    
    return data;
}
