#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../interfaces/IShape.hpp"
#include "../interfaces/IRenderer.hpp"

class Circle : public IShape {
public:
    Circle() = default;
    Circle(double cx, double cy, double radius = 50.0);

    void draw(IRenderer& renderer) const override;
    void resize(double factor) override;

    double getCx() const     { return cx_; }
    double getCy() const     { return cy_; }
    double getRadius() const { return radius_; }

private:
    double cx_ = 0.0;
    double cy_ = 0.0;
    double radius_ = 50.0;
};

#endif // CIRCLE_HPP