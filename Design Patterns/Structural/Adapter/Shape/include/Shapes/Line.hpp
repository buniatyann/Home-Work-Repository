#ifndef LINE_HPP
#define LINE_HPP

#include "../interface/IShape.hpp"
#include <iostream>

class Line : public IShape {
public:
    Line(const Coordinate& coord1, const Coordinate& coord2);

    void boundingBox() const override;
    void setBoundingBox(Coordinate coord1, Coordinate coord2) override;
    std::unique_ptr<Manipulator> createManipulator() const override;
    void giveDescription() const override;

    const Coordinate& getCoord1() const;
    const Coordinate& getCoord2() const;

private:
    Coordinate coord1_;
    Coordinate coord2_;
};

#endif // LINE_HPP
