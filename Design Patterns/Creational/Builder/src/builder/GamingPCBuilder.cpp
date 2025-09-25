#include "../../include/builder/GamingPCBuilder.hpp"

GamingPCBuilder::GamingPCBuilder() : pc(std::make_unique<PC>()) {}

GamingPCBuilder::GamingPCBuilder(const GamingPCBuilder& other) {
    if (other.pc) 
        pc = std::make_unique<PC>(*other.pc);
    else 
        pc = std::make_unique<PC>();
}

GamingPCBuilder::GamingPCBuilder(GamingPCBuilder&& other) noexcept : pc(std::move(other.pc)) {}

GamingPCBuilder& GamingPCBuilder::operator=(const GamingPCBuilder& other) {
    if (this == &other) 
        return *this;

    if (other.pc) 
        pc = std::make_unique<PC>(*other.pc);
    else 
        pc = std::make_unique<PC>();
    
    return *this;
}

GamingPCBuilder& GamingPCBuilder::operator=(GamingPCBuilder&& other) noexcept {
    if (this == &other) 
        return *this;

    pc = std::move(other.pc);
    return *this;
}

void GamingPCBuilder::setCPU(const std::string& cpu) { 
    pc->cpu = cpu; 
}

void GamingPCBuilder::setGPU(const std::string& gpu) { 
    pc->gpu = gpu; 
}

void GamingPCBuilder::setRAM(unsigned ramGB) { 
    pc->ramGB = ramGB; 
}

void GamingPCBuilder::setStorage(unsigned storageGB) { 
    pc->storageGB = storageGB; 
}

void GamingPCBuilder::setPSU(const std::string& psu) { 
    pc->psu = psu; 
}

void GamingPCBuilder::setCase(const std::string& pcCase) { 
    pc->pcCase = pcCase; 
}

PC GamingPCBuilder::getPC() { 
    return *pc; 
}
