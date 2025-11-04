#include "../../include/Decorators/ColoredShapeDecorator.hpp"

ColoredShapeDecorator::ColoredShapeDecorator(std::unique_ptr<IShape>&& shape, const std::string& color)
    : ShapeDecorator(std::move(shape)), color(color) {}

void ColoredShapeDecorator::draw() {
    shape->draw();
    std::cout << " with color " << color << std::endl;
}

void ColoredShapeDecorator::info() {
    shape->info();
    std::cout << " with color " << color << std::endl;
}
