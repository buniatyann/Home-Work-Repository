#ifndef PCDIRECTOR_HPP
#define PCDIRECTOR_HPP

#include "../interface/PCBuilder.hpp"

class PCDirector {
public:
    explicit PCDirector(std::unique_ptr<PCBuilder> b);
    PC buildPC(const std::string& cpu, const std::string& gpu, int ram, int storage,
               const std::string& psu, const std::string& pcCase);
private:
    std::unique_ptr<PCBuilder> builder;
};

#endif
