#include "../../include/Vihecle Factory/FordFactory.hpp"
#include "../../include/Engine/FordEngine.hpp"
#include "../../include/Wheel/FordWheel.hpp"
#include <iostream>

std::unique_ptr<IEngine> FordFactory::createEngine() const {
    return std::make_unique<FordEngine>();
}

std::unique_ptr<IWheel> FordFactory::createWheel() const {
    return std::make_unique<FordWheel>();
}

void FordFactory::assembleSedan() const {
    auto engine = createEngine();
    auto wheel = createWheel();
    std::cout << "Assembling Ford Sedan:" << std::endl;
    engine->install();
    for (int i = 0; i < 4; ++i) {
        wheel->install();
    }
}

void FordFactory::assembleSUV() const {
    auto engine = createEngine();
    auto wheel = createWheel();
    std::cout << "Assembling Ford SUV:" << std::endl;
    engine->install();
    for (int i = 0; i < 4; ++i) {
        wheel->install();
    }
}