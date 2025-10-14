#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "IGraphObject.hpp"

class Rectangle : public IGraphObject {
public:
    virtual void draw() const override {
        std::cout << "Rectangle " << std::endl;
    }
};

#endif // RECTANGLE_HPP