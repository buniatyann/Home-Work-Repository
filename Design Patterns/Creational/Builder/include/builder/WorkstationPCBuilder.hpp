#ifndef WORKSTABUILDER_HPP
#define WORKSTATIONBUILDER_HPP

#include "../interface/PCBuilder.hpp"
#include "../product/PC.hpp"


class WorkstationPCBuilder : public PCBuilder {
public:
    WorkstationPCBuilder();
    WorkstationPCBuilder(const WorkstationPCBuilder& other);
    WorkstationPCBuilder(WorkstationPCBuilder&& other) noexcept;
    WorkstationPCBuilder& operator=(const WorkstationPCBuilder& other);
    WorkstationPCBuilder& operator=(WorkstationPCBuilder&& other) noexcept;

    void setCPU(const std::string& cpu) override;
    void setGPU(const std::string& gpu) override;
    void setRAM(unsigned ramGB) override;
    void setStorage(unsigned storageGB) override;
    void setPSU(const std::string& psu) override;
    void setCase(const std::string& pcCase) override;
    PC getPC() override;
    
private:
    std::unique_ptr<PC> pc;
};

#endif // WORKSTATIONBUILDER_HPP