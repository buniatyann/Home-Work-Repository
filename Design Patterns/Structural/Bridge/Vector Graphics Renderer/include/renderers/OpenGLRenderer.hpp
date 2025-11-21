#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "../interfaces/IRenderer.hpp"

class OpenGLRenderer : public IRenderer {
public:
    void beginFrame() override;
    void endFrame() override;
    void draw(const IShape& shape) override;
};

#endif // OPENGL_RENDERER_HPP