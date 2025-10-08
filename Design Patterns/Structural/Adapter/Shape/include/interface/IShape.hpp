#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <utility>
#include <memory>
#include <iostream>
#include "../Manipulator/Manipulator.hpp"
class Manipulator {
public:
    void print() {
        std::cout << "Manipulator does something" << std::endl;
    }
};

class IShape {
public:
    using Point = double;
    using Coordinate = std::pair<Point, Point>;

    virtual ~IShape() = default;
    virtual void boundingBox() const = 0;
    virtual void setBoundingBox(Coordinate t1, Coordinate t2) = 0;
    virtual std::unique_ptr<Manipulator> createManipulator() const = 0;
    virtual void giveDescription() const = 0;
};

#endif // ISHAPE_HPP
