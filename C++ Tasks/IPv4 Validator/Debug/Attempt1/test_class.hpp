#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <string>

std::string createIPAddress();  // Function to create a random IP address.
void createTestFile(u_int32_t size, const std::string& filename);

class TestFileGenerator final {
public:
    explicit TestFileGenerator(u_int32_t size = 1, const std::string& name = "file.txt")
        : size_(size), filename_(name) {}
    
    // Deleted copy/move constructors and assignment operators to prevent copying/moving
    TestFileGenerator(const TestFileGenerator& rhs) = delete;
    TestFileGenerator& operator=(const TestFileGenerator& rhs) = delete;
    TestFileGenerator(TestFileGenerator&& rhs) = delete;
    TestFileGenerator& operator=(TestFileGenerator&& rhs) = delete;

    void createTestFile();

private:
    std::string createIPAddress();  // Helper function to create an IP address.

private:
    std::string filename_;
    u_int32_t size_;
};

#endif
