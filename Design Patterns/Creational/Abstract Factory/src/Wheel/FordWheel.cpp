#include "../../include/Wheel/FordWheel.hpp"
#include <iostream>

void FordWheel::install() const {
    std::cout << "Installing Ford Wheel" << std::endl;
}

std::unique_ptr<IWheel> FordWheel::clone() const {
    return std::make_unique<FordWheel>(*this);
}