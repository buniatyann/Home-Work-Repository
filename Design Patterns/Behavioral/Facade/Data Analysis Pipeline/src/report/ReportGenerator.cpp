#include "../../include/report/ReportGenerator.hpp"
#include <fstream>
#include <iostream>

void ReportGenerator::generate(const std::string& result, const std::string& outFile) {
    std::ofstream file(outFile);
    if (!file) {
        std::cerr << "Failed to create report: " << outFile << "\n";
        return;
    }

    file << "Analysis Report:\n";
    file << result << "\n";
}
