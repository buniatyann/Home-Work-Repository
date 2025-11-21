#ifndef ISHAPE_HPP
#define ISHAPE_HPP

class IRenderer;

class IShape {
public:
    virtual ~IShape() = default;
    virtual void draw(IRenderer& renderer) const = 0;
    virtual void resize(double factor) = 0;
};

#endif // ISHAPE_HPP