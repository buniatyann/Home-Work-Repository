#include "../../include/Shapes/Rectangle.hpp"

void Rectangle::draw() {
    std::cout << "Drawing rectangle" << std::endl;
}

void Rectangle::info() {
    std::cout << "This is a Rectangle" << std::endl;
}

Rectangle::~Rectangle() = default;
