#include "../../include/Engine/FordEngine.hpp"
#include <iostream>

void FordEngine::install() const {
    std::cout << "Installing Ford Engine" << std::endl;
}

std::unique_ptr<IEngine> FordEngine::clone() const {
    return std::make_unique<FordEngine>(*this);
}