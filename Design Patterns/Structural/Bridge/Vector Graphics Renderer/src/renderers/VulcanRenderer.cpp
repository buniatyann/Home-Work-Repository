#include "include/renderers/VulcanRenderer.hpp"
#include "include/shapes/Circle.hpp"
#include "include/shapes/Rectangle.hpp"
#include "include/shapes/Triangle.hpp"
#include <iostream>
#include <typeinfo>

void VulcanRenderer::beginFrame() {
    std::cout << "{\n  \"engine\": \"Vulcan\",\n  \"scene\": [\n";
    first_ = true;
}

void VulcanRenderer::endFrame() {
    std::cout << "\n  ]\n}\n";
}

void VulcanRenderer::draw(const IShape& shape) {
    if (!first_) std::cout << ",\n";
    first_ = false;

    if (typeid(shape) == typeid(Circle)) {
        const auto& c = static_cast<const Circle&>(shape);
        std::cout << "    { \"type\": \"circle\", \"center\": [" << c.getCx() << ", " << c.getCy()
                  << "], \"radius\": " << c.getRadius() << " }";
    }
    else if (typeid(shape) == typeid(Rectangle)) {
        const auto& r = static_cast<const Rectangle&>(shape);
        std::cout << "    { \"type\": \"rect\", \"pos\": [" << r.getX() << ", " << r.getY()
                  << "], \"size\": [" << r.getWidth() << ", " << r.getHeight() << "] }";
    }
    else if (typeid(shape) == typeid(Triangle)) {
        const auto& t = static_cast<const Triangle&>(shape);
        std::cout << "    { \"type\": \"triangle\", \"vertices\": ["
                  << "[" << t.getX1() << "," << t.getY1() << "],"
                  << "[" << t.getX2() << "," << t.getY2() << "],"
                  << "[" << t.getX3() << "," << t.getY3() << "]] }";
    }
}