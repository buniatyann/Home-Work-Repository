#include <iostream>
#include <fstream>
#include <bitset>
#include <string_view>
#include <sstream>
#include <stdexcept>

constexpr uint32_t MAX_IPV4 = 4294967296ULL; // 2^32

uint32_t ipToInt(std::string_view str) {
    uint32_t ans = 0;
    size_t start = 0;
    int octet_count = 0;

    for (int shift = 24; shift >= 0; shift -= 8) {
        size_t end = str.find('.', start);
        if (end == std::string_view::npos) {
            end = str.length();
        }
        
        if (start >= end) {
            throw std::invalid_argument("Invalid IP format");
        }

        std::string octet_str(str.substr(start, end - start));
        std::size_t pos;
        int byte = std::stoi(octet_str, &pos);
        if (pos != octet_str.length() || byte < 0 || byte > 255) {
            throw std::out_of_range("IP octet out of range or malformed");
        }
        
        ans |= (static_cast<uint32_t>(byte) << shift);
        start = end + 1;
        octet_count++;
    }

    if (octet_count != 4 || start <= str.length()) {
        throw std::invalid_argument("IP must have exactly 4 octets");
    }
    
    return ans;
}

uint32_t find(const std::string& name) {
    std::ifstream iff(name);
    if (!iff) {
        std::cerr << "Cannot open the file: " << name << std::endl;
        return UINT32_MAX; // Error indicator
    }

    uint32_t size;
    iff >> size;
    if (!iff) {
        std::cerr << "Failed to read size from file" << std::endl;
        return UINT32_MAX;
    }

    std::bitset<MAX_IPV4> bits; 
    std::string ip;
    for (uint32_t i = 0; i < size && iff >> ip; ++i) {
        try {
            uint32_t ipInt = ipToInt(ip);
            bits.set(ipInt);
        } 
        catch (const std::exception& e) {
            std::cerr << "Invalid IP '" << ip << "': " << e.what() << std::endl;
            return UINT32_MAX;
        }
    }

    if (iff.fail() && !iff.eof()) {
        std::cerr << "Error reading IPs from file" << std::endl;
        return UINT32_MAX;
    }

    return static_cast<uint32_t>(bits.count());
}
