#include <iostream>
#include <memory>
#include <vector>
#include "include/interfaces/IShape.hpp"
#include "include/interfaces/IRenderer.hpp"
#include "include/shapes/Circle.hpp"
#include "include/shapes/Rectangle.hpp"
#include "include/shapes/Triangle.hpp"
#include "include/renderers/SVGRenderer.hpp"
#include "include/renderers/VulcanRenderer.hpp"
#include "include/renderers/OpenGLRenderer.hpp"

int main() {
    std::cout << "=== Vector Graphics Renderer - Bridge Pattern Demo ===\n\n";

    std::vector<std::unique_ptr<IShape>> scene; // scene creation
    scene.emplace_back(std::make_unique<Circle>(400, 300, 120));
    scene.emplace_back(std::make_unique<Rectangle>(100, 100, 600, 400));
    scene.emplace_back(std::make_unique<Triangle>(400, 100, 200, 500, 600, 500));
    scene.emplace_back(std::make_unique<Circle>(200, 400, 80));

    // === 1. SVG Renderer ===
    {
        SVGRenderer svg("demo_scene.svg");
        std::cout << "Rendering to SVG file (demo_scene.svg)...\n";
        svg.beginFrame();
        for (const auto& shape : scene) {
            shape->draw(svg);
        }
        svg.endFrame();
        std::cout << "SVG rendering complete!\n\n";
    }

    // === 2. Vulcan Renderer (JSON-style output) ===
    {
        std::cout << "Rendering with Vulcan Engine (JSON-like format):\n\n";
        VulcanRenderer vulcan;
        vulcan.beginFrame();
        for (const auto& shape : scene) {
            shape->draw(vulcan);
        }

        vulcan.endFrame();
        std::cout << "\n";
    }

    // === 3. OpenGL Renderer (simulated GPU calls) ===
    {
        std::cout << "Rendering with OpenGL backend (immediate mode simulation):\n\n";
        OpenGLRenderer gl;
        gl.beginFrame();
        for (const auto& shape : scene) {
            shape->draw(gl);
        }

        gl.endFrame();
        std::cout << "\n";
    }

    std::cout << "Runtime switch demo: resizing all shapes by 0.7x and re-rendering to console...\n\n";
    for (auto& shape : scene) {
        shape->resize(0.7);
    }

    VulcanRenderer vulcan2;
    vulcan2.beginFrame();
    for (const auto& shape : scene) {
        shape->draw(vulcan2);
    }
 
    vulcan2.endFrame();
    std::cout << "\nAll done! Check demo_scene.svg in your folder.\n";
    return 0;
}