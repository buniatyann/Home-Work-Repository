#ifndef IRENDERER_HPP
#define IRENDERER_HPP

class IShape;

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void draw(const IShape& shape) = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
};

#endif // IRENDERER_HPP