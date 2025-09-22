#include "../../include/Vihecle Factory/ToyotaFactory.hpp"
#include "../../include/Engine/ToyotaEngine.hpp"
#include "../../include/Wheel/ToyotaWheel.hpp"
#include <iostream>

std::unique_ptr<IEngine> ToyotaFactory::createEngine() const {
    return std::make_unique<ToyotaEngine>();
}

std::unique_ptr<IWheel> ToyotaFactory::createWheel() const {
    return std::make_unique<ToyotaWheel>();
}

void ToyotaFactory::assembleSedan() const {
    auto engine = createEngine();
    auto wheel = createWheel();
    std::cout << "Assembling Toyota Sedan:" << std::endl;
    engine->install();
    for (int i = 0; i < 4; ++i) {
        wheel->install();
    }
}

void ToyotaFactory::assembleSUV() const {
    auto engine = createEngine();
    auto wheel = createWheel();
    std::cout << "Assembling Toyota SUV:" << std::endl;
    engine->install();
    for (int i = 0; i < 4; ++i) {
        wheel->install();
    }
}