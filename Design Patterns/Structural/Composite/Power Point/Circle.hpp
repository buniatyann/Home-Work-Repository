#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "IGraphObject.hpp"

class Circle : public IGraphObject {
public:
    void draw() const override {
        std::cout << "Cricle " << std::endl;
    }
};


#endif // CIRCLE_HPP