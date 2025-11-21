#include "include/shapes/Triangle.hpp"

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3) {}

void Triangle::draw(IRenderer& renderer) const {
    renderer.draw(*this);
}

void Triangle::resize(double factor) {
    double cx = (x1_ + x2_ + x3_) / 3.0;
    double cy = (y1_ + y2_ + y3_) / 3.0;

    x1_ = cx + (x1_ - cx) * factor;
    y1_ = cy + (y1_ - cy) * factor;
    x2_ = cx + (x2_ - cx) * factor;
    y2_ = cy + (y2_ - cy) * factor;
    x3_ = cx + (x3_ - cx) * factor;
    y3_ = cy + (y3_ - cy) * factor;
}