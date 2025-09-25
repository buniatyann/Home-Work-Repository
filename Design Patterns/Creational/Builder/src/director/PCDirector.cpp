#include "../../include/director/PCDirector.hpp"

PCDirector::PCDirector(std::unique_ptr<PCBuilder> b)
    : builder(std::move(b)) {}

PC PCDirector::buildPC(const std::string& cpu, const std::string& gpu, int ram, int storage,
                       const std::string& psu, const std::string& pcCase) {
    builder->setCPU(cpu);
    builder->setGPU(gpu);
    builder->setRAM(ram);
    builder->setStorage(storage);
    builder->setPSU(psu);
    builder->setCase(pcCase);

    return builder->getPC();
}
    