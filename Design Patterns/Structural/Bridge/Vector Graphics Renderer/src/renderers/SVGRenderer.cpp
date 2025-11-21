#include "include/renderers/SVGRenderer.hpp"
#include "include/shapes/Circle.hpp"
#include "include/shapes/Rectangle.hpp"
#include "include/shapes/Triangle.hpp"
#include <typeinfo>
#include <iostream>

SVGRenderer::SVGRenderer(const std::string& filename) {
    // file_.open(filename);
    std::cout << "[INFO] File: " << filename << " is opened" << std::endl;
    beginFrame();
}

SVGRenderer::~SVGRenderer() {
    endFrame();
    // file_.close();
}

void SVGRenderer::beginFrame() {
    std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    std::cout << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";
}

void SVGRenderer::endFrame() {
    std::cout << "</svg>\n";
}

void SVGRenderer::draw(const IShape& shape) {
    if (typeid(shape) == typeid(Circle)) {
        const auto& c = static_cast<const Circle&>(shape);
        std::cout << "  <circle cx=\"" << c.getCx() << "\" cy=\"" << c.getCy()
              << "\" r=\"" << c.getRadius() << "\" fill=\"none\" stroke=\"blue\" stroke-width=\"4\"/>\n";
    }
    else if (typeid(shape) == typeid(Rectangle)) {
        const auto& r = static_cast<const Rectangle&>(shape);
        std::cout << "  <rect x=\"" << r.getX() << "\" y=\"" << r.getY()
              << "\" width=\"" << r.getWidth() << "\" height=\"" << r.getHeight()
              << "\" fill=\"none\" stroke=\"red\" stroke-width=\"4\"/>\n";
    }
    else if (typeid(shape) == typeid(Triangle)) {
        const auto& t = static_cast<const Triangle&>(shape);
        std::cout << "  <polygon points=\""
              << t.getX1() << "," << t.getY1() << " "
              << t.getX2() << "," << t.getY2() << " "
              << t.getX3() << "," << t.getY3()
              << "\" fill=\"none\" stroke=\"green\" stroke-width=\"4\"/>\n";
    }
}