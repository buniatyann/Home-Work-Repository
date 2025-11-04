#include "../../include/Shapes/Triangle.hpp"

void Triangle::draw() {
    std::cout << "Drawing triangle" << std::endl;
}

void Triangle::info() {
    std::cout << "This is a Triangle" << std::endl;
}

Triangle::~Triangle() = default;
