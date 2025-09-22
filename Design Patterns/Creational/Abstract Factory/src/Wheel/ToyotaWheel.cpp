#include "../../include/Wheel/ToyotaWheel.hpp"
#include <iostream>

void ToyotaWheel::install() const {
    std::cout << "Installing Toyota Wheel" << std::endl;
}

std::unique_ptr<IWheel> ToyotaWheel::clone() const {
    return std::make_unique<ToyotaWheel>(*this);
}