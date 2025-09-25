#ifndef PC_HPP
#define PC_HPP

#include <string>
#include <iostream>

struct PC {
    void specs() const {
        std::cout << "CPU: " << cpu << "\n"
        << "GPU: " << gpu << "\n"
        << "RAM: " << ramGB << "GB\n"
        << "Storage: " << storageGB << "GB\n"
        << "PSU: " << psu << "\n"
        << "Case: " << pcCase << "\n";
    }

    std::string cpu;
    std::string gpu;
    std::string psu;
    std::string pcCase;
    int ramGB = 0;
    int storageGB = 0;
};

#endif // PC_HPP
