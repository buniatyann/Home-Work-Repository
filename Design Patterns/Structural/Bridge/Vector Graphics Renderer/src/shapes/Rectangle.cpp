#include "include/shapes/Rectangle.hpp"

Rectangle::Rectangle(double x, double y, double width, double height)
    : x_(x), y_(y), width_(width), height_(height) {}

void Rectangle::draw(IRenderer& renderer) const {
    renderer.draw(*this);
}

void Rectangle::resize(double factor) {
    width_ *= factor;
    height_ *= factor;
}