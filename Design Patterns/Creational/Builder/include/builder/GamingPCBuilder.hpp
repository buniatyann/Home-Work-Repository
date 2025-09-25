#ifndef GAMINGPCBUILDER_HPP
#define GAMINGPCBUILDER_HPP

#include "../interface/PCBuilder.hpp"
#include "../product/PC.hpp"


class GamingPCBuilder : public PCBuilder {
public:
    GamingPCBuilder();
    GamingPCBuilder(const GamingPCBuilder& other);
    GamingPCBuilder(GamingPCBuilder&& other) noexcept;
    GamingPCBuilder& operator=(const GamingPCBuilder& other);
    GamingPCBuilder& operator=(GamingPCBuilder&& other) noexcept;

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
#endif // GAMINGPCBUILDER_HPP