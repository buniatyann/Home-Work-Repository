#include "include/shapes/Circle.hpp"

Circle::Circle(double cx, double cy, double radius)
    : cx_(cx), cy_(cy), radius_(radius) {}

void Circle::draw(IRenderer& renderer) const {
    renderer.draw(*this);
}

void Circle::resize(double factor) {
    radius_ *= factor;
}