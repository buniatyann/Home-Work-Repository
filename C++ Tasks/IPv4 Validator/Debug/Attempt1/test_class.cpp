#include "Test.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>

std::string TestFileGenerator::createIPAddress() {
    std::ostringstream oss;
    oss << distribution_(generator_) << "."
        << distribution_(generator_) << "."
        << distribution_(generator_) << "."
        << distribution_(generator_);
    return oss.str();
}

void TestFileGenerator::createTestFile() {
    if (size_ == 0) {
        throw std::invalid_argument("Size must be greater than zero.");
    }

    std::ofstream outFile(filename_, std::ios::binary);
    if (!outFile) {
        throw std::ios_base::failure("Error opening file for writing: " + filename_);
    }

    std::vector<std::string> ipAddresses;
    ipAddresses.reserve(size_);

    for (u_int32_t i = 0; i < size_; ++i) {
        ipAddresses.push_back(createIPAddress());
    }

    for (const auto& ip : ipAddresses) {
        outFile << ip << std::endl;
    }

    std::cout << "Test file '" << filename_ << "' created with " << size_ << " IP addresses." << std::endl;
}
