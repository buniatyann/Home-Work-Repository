#include "include/builder/GamingPCBuilder.hpp"
#include "include/builder/WorkstationPCBuilder.hpp"
#include "include/director/PCDirector.hpp"

int main() {
    auto gamingBuilder = std::make_unique<GamingPCBuilder>();
    PCDirector director1(std::move(gamingBuilder));
    PC gamingPC = director1.buildPC("Intel i9-14900HX", "NVIDIA RTX 4090", 32, 2000, "850W Gold", "RGB Tower");

    auto workstationBuilder = std::make_unique<WorkstationPCBuilder>();
    PCDirector director2(std::move(workstationBuilder));
    PC workstationPC = director2.buildPC("AMD Threadripper", "NVIDIA Quadro RTX", 256, 4000, "1000W Platinum", "Server Case");

    gamingPC.specs();
    std::cout << "\n";
    workstationPC.specs();

    return 0;
}
