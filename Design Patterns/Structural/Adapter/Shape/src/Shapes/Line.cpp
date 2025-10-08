#include "../../include/Shapes/Line.hpp"

Line::Line(const Coordinate& coord1, const Coordinate& coord2)
    : coord1_(coord1), coord2_(coord2) {}

void Line::boundingBox() const {
    std::cout << "Line with coordinates (" << coord1_.first << ", " << coord1_.second
              << ") and (" << coord2_.first << ", " << coord2_.second << ")\n";
}

void Line::setBoundingBox(Coordinate coord1, Coordinate coord2) {
    coord1_ = coord1;
    coord2_ = coord2;
    std::cout << "Coordinates are set\n";
}

std::unique_ptr<Manipulator> Line::createManipulator() const {
    return std::make_unique<Manipulator>();
}

void Line::giveDescription() const {
    std::cout << "This is a line defined by two endpoints.\n";
}

const IShape::Coordinate& Line::getCoord1() const {
    return coord1_;
}

const IShape::Coordinate& Line::getCoord2() const {
    return coord2_;
}
