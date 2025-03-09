#include "test_class.hpp"

std::string createIPAddress() {
    // Create a random IP address.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::stringstream ip;
    ip << dis(gen) << "."
        << dis(gen) << "."
        << dis(gen) << "."
        << dis(gen);
    
        return ip.str();
}

void createTestFile(u_int32_t size, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    outFile << size << std::endl;  // Write the size (number of IPs) to the file
    for (u_int32_t i = 0; i < size; ++i) {
        outFile << createIPAddress() << std::endl;  // Write each generated IP
    }
}

void TestFileGenerator::createTestFile(u_int32_t size, std::string& filename)
{
    createTestFile(this->size_, filename);
}



// #include "test.hpp"

// std::string createIPAddress()
// {
//     static std::random_device rd;   // Non-deterministic seed
//     static std::mt19937 gen(rd());  // Mersenne Twister RNG
//     static std::uniform_int_distribution<int> dist(0, 255);  // Uniform distribution for 0-255

//     std::ostringstream ip;
//     ip << dist(gen) << "." << dist(gen) << "." << dist(gen) << "." << dist(gen);
    
//     return ip.str();
// }

// void createTestFile(u_int32_t size)
// {
//     if (size == 0) {
//         std::cerr << "Error: Size must be greater than 0!" << std::endl;
//         return;
//     }

//     std::ofstream file("test.txt");
//     if (!file) {
//         std::cerr << "Error: Could not open file for writing!" << std::endl;
//         return;
//     }

//     std::vector<std::string> ipAddresses;
//     ipAddresses.reserve(size);  // Reserve memory to prevent multiple allocations

//     for (uint32_t i = 0; i < size; ++i) {
//         ipAddresses.push_back(createIPAddress());
//     }

//     // Write size and IP addresses efficiently
//     file << size << "\n";
//     for (const auto& ip : ipAddresses) {
//         file << ip << "\n";
//     }

//     std::cout << "Data created successfully!" << std::endl;
// }

