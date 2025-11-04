#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "../Interface/IShape.hpp"

class Triangle : public IShape {
public:
    void draw() override;
    void info() override;
    ~Triangle() override;
};

#endif // TRIANGLE_HPP
