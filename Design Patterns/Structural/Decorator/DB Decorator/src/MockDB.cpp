#include "../include/decorators/MockDB.hpp"
#include <iostream>

std::string MockDB::execute(const std::string& query,
                            const std::unordered_map<std::string, std::string>& params) {
    std::cout << "[MockDB] RUN: " << query << "\n";
    if (!params.empty()) {
        std::cout << "    params: ";
        for (const auto& [k, v] : params) 
            std::cout << k << "=" << v << " ";
        std::cout << "\n";
    }

    return "[MockResult] OK – " + query;
}