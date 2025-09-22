#include "../../include/Engine/ToyotaEngine.hpp"
#include <iostream>

void ToyotaEngine::install() const {
    std::cout << "Installing Toyota Engine" << std::endl;
}

std::unique_ptr<IEngine> ToyotaEngine::clone() const {
    return std::make_unique<ToyotaEngine>(*this);
}