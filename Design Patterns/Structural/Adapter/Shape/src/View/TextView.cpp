#include "../../include/View/TextView.hpp"

TextView::TextView(std::string text, Coordinate topLeft, Coordinate bottomRight)
    : text_(std::move(text)), topLeft_(topLeft), bottomRight_(bottomRight) {}

void TextView::getExtent(Coordinate& bottomLeft, Coordinate& topRight) const {
    bottomLeft = topLeft_;
    topRight = bottomRight_;
}

std::string TextView::getText() const {
    return text_;
}
