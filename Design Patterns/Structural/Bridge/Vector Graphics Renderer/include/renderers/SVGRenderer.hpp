#ifndef SVG_RENDERER_HPP
#define SVG_RENDERER_HPP

#include "../interfaces/IRenderer.hpp"
#include <fstream>
#include <string>

class SVGRenderer : public IRenderer {
    // std::ofstream file_;
public:
    explicit SVGRenderer(const std::string& filename = "output.svg");
    ~SVGRenderer() override;

    void beginFrame() override;
    void endFrame() override;
    void draw(const IShape& shape) override;
};

#endif // SVG_RENDERER_HPP