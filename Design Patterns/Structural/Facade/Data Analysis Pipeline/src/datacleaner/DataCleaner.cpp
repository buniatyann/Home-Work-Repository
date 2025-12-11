#include "../../include/datacleaner/DataCleaner.hpp"
#include <algorithm>

std::vector<std::string> DataCleaner::clean(const std::vector<std::string>& rawData) {
    std::vector<std::string> result;
    for (auto& line : rawData) {
        if (!line.empty()) {
            std::string trimmed = line;
            trimmed.erase(trimmed.begin(),
                std::find_if(trimmed.begin(), trimmed.end(), [](char ch) { return !std::isspace(ch); }));
            trimmed.erase(
                std::find_if(trimmed.rbegin(), trimmed.rend(),
                    [](char ch) { return !std::isspace(ch); }).base(),
                trimmed.end());

            if (!trimmed.empty())
                result.push_back(trimmed);
        }
    }

    return result;
}
