#ifndef COLORED_SHAPE_DECORATOR_HPP
#define COLORED_SHAPE_DECORATOR_HPP

#include "ShapeDecorator.hpp"
#include <string>

class ColoredShapeDecorator : public ShapeDecorator {
public:
    ColoredShapeDecorator(std::unique_ptr<IShape>&& shape, const std::string& color);
    void draw() override;
    void info() override;

private:
    std::string color;
};

#endif // COLORED_SHAPE_DECORATOR_HPP
