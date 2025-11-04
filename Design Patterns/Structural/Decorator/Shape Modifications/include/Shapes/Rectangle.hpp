#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../Interface/IShape.hpp"

class Rectangle : public IShape {
public:
    void draw() override;
    void info() override;
    ~Rectangle() override;
};

#endif // RECTANGLE_HPP
