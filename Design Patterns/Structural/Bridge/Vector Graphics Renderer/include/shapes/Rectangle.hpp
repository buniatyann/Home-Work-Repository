#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../interfaces/IShape.hpp"
#include "../interfaces/IRenderer.hpp"

class Rectangle : public IShape {
public:
    Rectangle() = default;
    Rectangle(double x, double y, double width, double height);

    void draw(IRenderer& renderer) const override;
    void resize(double factor) override;

    double getX() const      { return x_; }
    double getY() const      { return y_; }
    double getWidth() const  { return width_; }
    double getHeight() const { return height_; }

private:
    double x_ = 0.0;
    double y_ = 0.0;
    double width_ = 100.0;
    double height_ = 100.0;
};

#endif // RECTANGLE_HPP