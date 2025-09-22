#ifndef VEHICLE_ASSEMBLY_LINE_HPP
#define VEHICLE_ASSEMBLY_LINE_HPP

#include "../Interfaces/IVehicleFactory.hpp"
#include <memory>
#include <string>
#include <vector>
#include <tuple>

class VehicleAssemblyLine {
public:
    VehicleAssemblyLine();
    void setFactory(std::unique_ptr<IVehicleFactory> factory);
    void assembleVehicle(const std::string& type);
    const std::vector<std::tuple<std::unique_ptr<IEngine>, std::unique_ptr<IWheel>, std::string, std::string>>& getHistory() const;
    void replayAssembly(size_t index) const;

private:
    std::unique_ptr<IVehicleFactory> factory_;
    std::vector<std::tuple<std::unique_ptr<IEngine>, std::unique_ptr<IWheel>, std::string, std::string>> history_;
};

#endif // VEHICLE_ASSEMBLY_LINE_HPP