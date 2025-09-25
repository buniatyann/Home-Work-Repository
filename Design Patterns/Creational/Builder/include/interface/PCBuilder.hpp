#ifndef PCBUILDER_HPP
#define PCBUILDER_HPP

#include "product/PC.hpp"
#include <memory>

class PCBuilder {
public:
    virtual ~PCBuilder() = default;
    virtual void setCPU(const std::string& cpu) = 0;
    virtual void setGPU(const std::string& gpu) = 0;
    virtual void setRAM(unsigned  ramGB) = 0;
    virtual void setStorage(unsigned storageGB) = 0;
    virtual void setPSU(const std::string& psu) = 0;
    virtual void setCase(const std::string& pcCase) = 0;
    virtual PC getPC() = 0;
};

#endif // PCBUILDER_HPP
