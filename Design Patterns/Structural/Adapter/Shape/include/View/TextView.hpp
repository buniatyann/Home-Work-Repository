#ifndef TEXTVIEW_HPP
#define TEXTVIEW_HPP

#include <iostream>
#include <string>
#include <utility>

class TextView {
public:
    using Coordinate = std::pair<double, double>;

    TextView(std::string text, Coordinate topLeft, Coordinate bottomRight);

    void getExtent(Coordinate& bottomLeft, Coordinate& topRight) const;
    std::string getText() const;

private:
    std::string text_;
    Coordinate topLeft_;
    Coordinate bottomRight_;
};

#endif // TEXTVIEW_HPP
