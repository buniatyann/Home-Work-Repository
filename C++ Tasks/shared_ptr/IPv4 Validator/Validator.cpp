#include <iostream>
#include <fstream>
#include <bitset>
#include <string_view>
#include <sstream>
#include "test.hpp"

u_int32_t ipToInt(std::string_view str) {
    u_int32_t ans = 0;
    size_t start = 0;
    u_int32_t shift = 24;

    for (size_t i = 0; i < 4; ++i) {
        size_t end = str.find('.', start);
        if (end == std::string_view::npos) {
            end = str.length();  // Last part of the IP
        }

        // Parse the byte part of the IP address
        u_int32_t byte = std::stoi(std::string(str.substr(start, end - start)));
        ans |= (byte << shift);  // Shift and OR to accumulate the result
        shift -= 8;
        start = end + 1;
    }

    return ans;
}

u_int32_t find(const std::string& name) {
    std::ifstream iff(name);
    u_int32_t size;
    std::bitset<255255255256> bits;

    if (!iff) {
        std::cerr << "Cannot open the file" << std::endl;
        return 1;
    }

    iff >> size;  // Read the number of IPs
    std::string Ip;
    for (u_int32_t i = 0; i < size; ++i) {
        iff >> Ip;
        std::string_view ipView(Ip);  // Use string_view to avoid copying the string
        u_int32_t ipInt = ipToInt(ipView);
        bits.set(ipInt);  // Set the bit corresponding to this IP
    }

    return static_cast<u_int32_t>(bits.count());  // Count the set bits (unique IPs)
}


int main() {
    u_int32_t numIPs;
    std::cout << "Enter the number of IP addresses to generate: ";
    std::cin >> numIPs;

    // Ask the user for the filename to save the generated IPs
    std::string filename;
    std::cout << "Enter the filename to save the IP addresses: ";
    std::cin >> filename;

    // Generate and save the IP addresses to the file
    createTestFile(numIPs, filename);

    std::cout << "Test file '" << filename << "' has been created with " << numIPs << " IP addresses." << std::endl;
    find(filename);

    
    return 0;
}

