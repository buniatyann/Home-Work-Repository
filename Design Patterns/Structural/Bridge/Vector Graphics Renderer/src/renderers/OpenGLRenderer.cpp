#include "include/renderers/OpenGLRenderer.hpp"
#include "include/shapes/Circle.hpp"
#include "include/shapes/Rectangle.hpp"
#include "include/shapes/Triangle.hpp"
#include <iostream>
#include <cmath>
#include <typeinfo>

void OpenGLRenderer::beginFrame() {
    std::cout << "glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);\n";
    std::cout << "glLoadIdentity();\n\n";
}

void OpenGLRenderer::endFrame() {
    std::cout << "\n// SwapBuffers()\n";
}

void OpenGLRenderer::draw(const IShape& shape) {
    if (typeid(shape) == typeid(Circle)) {
        const auto& c = static_cast<const Circle&>(shape);
        std::cout << "// Circle at (" << c.getCx() << "," << c.getCy() << ") r=" << c.getRadius() << "\n";
        std::cout << "glBegin(GL_TRIANGLE_FAN);\n";
        std::cout << "  glVertex2f(" << c.getCx() << "f, " << c.getCy() << "f);\n";
        for (int i = 0; i <= 32; ++i) {
            float angle = i * 2.0f * 3.14159f / 32;
            float x = c.getCx() + c.getRadius() * std::cos(angle);
            float y = c.getCy() + c.getRadius() * std::sin(angle);
            std::cout << "  glVertex2f(" << x << "f, " << y << "f);\n";
        }
        
        std::cout << "glEnd();\n\n";
    }
    else if (typeid(shape) == typeid(Rectangle)) {
        const auto& r = static_cast<const Rectangle&>(shape);
        float x2 = r.getX() + r.getWidth();
        float y2 = r.getY() + r.getHeight();
        std::cout << "glBegin(GL_LINE_LOOP);\n";
        std::cout << "  glVertex2f(" << r.getX()  << "f, " << r.getY()  << "f);\n";
        std::cout << "  glVertex2f(" << x2 << "f, " << r.getY()  << "f);\n";
        std::cout << "  glVertex2f(" << x2 << "f, " << y2 << "f);\n";
        std::cout << "  glVertex2f(" << r.getX()  << "f, " << y2 << "f);\n";
        std::cout << "glEnd();\n\n";
    }
    else if (typeid(shape) == typeid(Triangle)) {
        const auto& t = static_cast<const Triangle&>(shape);
        std::cout << "glBegin(GL_TRIANGLES);\n";
        std::cout << "  glVertex2f(" << t.getX1() << "f, " << t.getY1() << "f);\n";
        std::cout << "  glVertex2f(" << t.getX2() << "f, " << t.getY2() << "f);\n";
        std::cout << "  glVertex2f(" << t.getX3() << "f, " << t.getY3() << "f);\n";
        std::cout << "glEnd();\n\n";
    }
}