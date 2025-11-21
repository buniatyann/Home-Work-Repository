#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "../interfaces/IShape.hpp"
#include "../interfaces/IRenderer.hpp"

class Triangle : public IShape {
public:
    Triangle() = default;
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);

    void draw(IRenderer& renderer) const override;
    void resize(double factor) override;

    double getX1() const { return x1_; } double getY1() const { return y1_; }
    double getX2() const { return x2_; } double getY2() const { return y2_; }
    double getX3() const { return x3_; } double getY3() const { return y3_; }

private:
    double x1_ = 0,   y1_ = 100;
    double x2_ = 100, y2_ = 100;
    double x3_ = 50,  y3_ = 0;
};

#endif // TRIANGLE_HPP