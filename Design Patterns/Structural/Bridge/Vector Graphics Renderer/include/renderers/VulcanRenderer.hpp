#ifndef VULCAN_RENDERER_HPP
#define VULCAN_RENDERER_HPP

#include "../interfaces/IRenderer.hpp"

class VulcanRenderer : public IRenderer {
public:
    VulcanRenderer() { beginFrame(); }
    ~VulcanRenderer() override { endFrame(); }

    void beginFrame() override;
    void endFrame() override;
    void draw(const IShape& shape) override;

private:
    bool first_ = true;
};

#endif // VULCAN_RENDERER_HPP