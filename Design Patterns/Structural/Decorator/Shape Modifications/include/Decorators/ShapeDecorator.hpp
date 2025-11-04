#ifndef SHAPE_DECORATOR_HPP
#define SHAPE_DECORATOR_HPP

#include "../Interface/IShape.hpp"

class ShapeDecorator : public IShape {
public:
    ShapeDecorator(std::unique_ptr<IShape>&& shape);
    virtual void draw() override;
    virtual void info() override;
    virtual ~ShapeDecorator() = default;

protected:
    std::unique_ptr<IShape> shape;
};

#endif // SHAPE_DECORATOR_HPP
