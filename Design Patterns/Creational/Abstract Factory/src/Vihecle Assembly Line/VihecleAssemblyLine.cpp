#include "../../include/Vihecle Assembly Line/VehicleAssemblyLine.hpp"
#include "../../include/Vihecle Factory/ToyotaFactory.hpp"
#include "../../include/Vihecle Factory/FordFactory.hpp"
#include <stdexcept>
#include <iostream>

VehicleAssemblyLine::VehicleAssemblyLine() : factory_(std::make_unique<ToyotaFactory>()) {}

void VehicleAssemblyLine::setFactory(std::unique_ptr<IVehicleFactory> factory) {
    factory_ = std::move(factory);
}

void VehicleAssemblyLine::assembleVehicle(const std::string& type) {
    if (!factory_) {
        throw std::runtime_error("No factory set");
    }
    auto engine = factory_->createEngine();
    auto wheel = factory_->createWheel();
    if (type == "Sedan") {
        factory_->assembleSedan();
        history_.emplace_back(std::move(engine), std::move(wheel), type, "Toyota");
    } 
    else if (type == "SUV") {
        factory_->assembleSUV();
        history_.emplace_back(std::move(engine), std::move(wheel), type, "Toyota");
    } 
    else {
        throw std::invalid_argument("Unknown vehicle type: " + type);
    }
}

const std::vector<std::tuple<std::unique_ptr<IEngine>, std::unique_ptr<IWheel>, std::string, std::string>>& VehicleAssemblyLine::getHistory() const {
    return history_;
}

void VehicleAssemblyLine::replayAssembly(size_t index) const {
    if (index >= history_.size()) {
        throw std::out_of_range("Invalid history index");
    }
    
    const auto& [engine, wheel, type, manufacturer] = history_[index];
    std::cout << "Replaying assembly of " << manufacturer << " " << type << ":" << std::endl;
    engine->install();
    for (int i = 0; i < 4; ++i) {
        wheel->install();
    }
}