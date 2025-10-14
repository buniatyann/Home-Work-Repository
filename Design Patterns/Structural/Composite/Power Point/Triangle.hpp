#ifndef TRINANGLE_HPP
#define TRIANGLE_HPP

#include "IGraphObject.hpp"

class Triangle : public IGraphObject {
public:
    void draw() const override {
        std::cout << "Triangle " << std::endl;
    }
};

#endif // TRINAGLE_HPP