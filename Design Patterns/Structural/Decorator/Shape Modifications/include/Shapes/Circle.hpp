#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../Interface/IShape.hpp"

class Circle : public IShape {
public:
    void draw() override;
    void info() override;
    ~Circle() override;
};

#endif // CIRCLE_HPP
