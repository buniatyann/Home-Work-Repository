#include "../../include/Shapes/Circle.hpp"

void Circle::draw() {
    std::cout << "Drawing circle" << std::endl;
}

void Circle::info() {
    std::cout << "This is a circle" << std::endl;
}

Circle::~Circle() = default;
