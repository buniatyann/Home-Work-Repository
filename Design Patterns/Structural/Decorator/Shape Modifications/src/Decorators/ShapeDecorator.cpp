#include "../../include/Decorators/ShapeDecorator.hpp"

ShapeDecorator::ShapeDecorator(std::unique_ptr<IShape>&& shape) : shape(std::move(shape)) {}

void ShapeDecorator::draw() {
    shape->draw();
}

void ShapeDecorator::info() {
    shape->info();
}
