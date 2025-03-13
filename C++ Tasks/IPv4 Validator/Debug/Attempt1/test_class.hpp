#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <string>
#include <stdexcept>

class TestFileGenerator final {
public:
    explicit TestFileGenerator(u_int32_t size = 1, const std::string& name = "file.txt", unsigned int seed = 0)
        : size_(size), filename_(name), generator_(seed), distribution_(0, 255) {
        if (size_ <= 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }
    }
    
    TestFileGenerator(const TestFileGenerator& rhs) = delete;
    TestFileGenerator& operator=(const TestFileGenerator& rhs) = delete;
    TestFileGenerator(TestFileGenerator&& rhs) = delete;
    TestFileGenerator& operator=(TestFileGenerator&& rhs) = delete;

    void createTestFile();

private:
    std::string createIPAddress();

private:
    std::string filename_;
    u_int32_t size_;
    std::mt19937 generator_;
    std::uniform_int_distribution<> distribution_;
};

#endif
