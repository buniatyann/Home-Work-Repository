#include "include/Vihecle Assembly Line/VehicleAssemblyLine.hpp"
#include "include/Vihecle Factory/ToyotaFactory.hpp"
#include "include/Vihecle Factory/FordFactory.hpp"
#include <iostream>

int main() {
    VehicleAssemblyLine assemblyLine;
    try {
        std::cout << "Using Toyota Factory:\n";
        assemblyLine.assembleVehicle("Sedan");
        assemblyLine.assembleVehicle("SUV");
        assemblyLine.setFactory(std::make_unique<FordFactory>());
        std::cout << "\nUsing Ford Factory:\n";
        assemblyLine.assembleVehicle("Sedan");
        assemblyLine.assembleVehicle("SUV");
        std::cout << "\nReplaying Assembly History:\n";
        for (size_t i = 0; i < assemblyLine.getHistory().size(); ++i) {
            assemblyLine.replayAssembly(i);
        }
        assemblyLine.assembleVehicle("Truck");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nAssembly History:\n";
    for (const auto& [engine, wheel, type, manufacturer] : assemblyLine.getHistory()) {
        std::cout << "Manufacturer: " << manufacturer << ", Type: " << type << std::endl;
    }

    return 0;
}