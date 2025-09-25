#include "../../include/builder/WorkstationPCBuilder.hpp"

WorkstationPCBuilder::WorkstationPCBuilder() : pc(std::make_unique<PC>()) {}

WorkstationPCBuilder::WorkstationPCBuilder(const WorkstationPCBuilder& other) {
    if (other.pc) 
        pc = std::make_unique<PC>(*other.pc);
    else 
        pc = std::make_unique<PC>();
}

WorkstationPCBuilder::WorkstationPCBuilder(WorkstationPCBuilder&& other) noexcept : pc(std::move(other.pc)) {}

WorkstationPCBuilder& WorkstationPCBuilder::operator=(const WorkstationPCBuilder& other) {
    if (this == &other) 
        return *this;

    if (other.pc) 
        pc = std::make_unique<PC>(*other.pc);
    else 
        pc = std::make_unique<PC>();
    
    return *this;
}

WorkstationPCBuilder& WorkstationPCBuilder::operator=(WorkstationPCBuilder&& other) noexcept {
    if (this == &other) 
        return *this;

    pc = std::move(other.pc);
    return *this;
}

void WorkstationPCBuilder::setCPU(const std::string& cpu) { 
    pc->cpu = cpu; 
}

void WorkstationPCBuilder::setGPU(const std::string& gpu) { 
    pc->gpu = gpu; 
}

void WorkstationPCBuilder::setRAM(unsigned ramGB) { 
    pc->ramGB = ramGB; 
}

void WorkstationPCBuilder::setStorage(unsigned storageGB) { 
    pc->storageGB = storageGB; 
}

void WorkstationPCBuilder::setPSU(const std::string& psu) { 
    pc->psu = psu; 
}

void WorkstationPCBuilder::setCase(const std::string& pcCase) { 
    pc->pcCase = pcCase; 
}

PC WorkstationPCBuilder::getPC() { 
    return *pc; 
}
