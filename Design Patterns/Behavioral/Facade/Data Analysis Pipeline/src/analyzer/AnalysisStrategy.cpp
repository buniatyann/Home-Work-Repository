#include "../../include/analyzer/AnalysisStrategy.hpp"
#include <numeric>
#include <sstream>

std::string AverageAnalysis::analyze(const std::vector<std::string>& data) {
    double sum = 0;
    for (const auto& item : data) {
        sum += std::stod(item);
    }

    double average = sum / data.size();
    std::ostringstream result;
    result << "Average: " << average;
    return result.str();
}

std::string CustomAnalysis::analyze(const std::vector<std::string>& data) {
    std::ostringstream result;
    result << "Custom Analysis: Processed " << data.size() << " items.";
    
    return result.str();
}
