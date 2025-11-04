#ifndef I_SHAPE_HPP
#define I_SHAPE_HPP

#include <memory>
#include <iostream>

class IShape {
public:
    virtual ~IShape() = default;
    virtual void draw() = 0;
    virtual void info() = 0;
};

#endif // I_SHAPE_HPP
