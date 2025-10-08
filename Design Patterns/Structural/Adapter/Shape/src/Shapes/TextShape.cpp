#include "../../include/Shapes/TextShape.hpp"

TextShape::TextShape(std::unique_ptr<TextView> textView)
    : textView_(std::move(textView)) {}

void TextShape::boundingBox() const {
    TextView::Coordinate bottomLeft, topRight;
    textView_->getExtent(bottomLeft, topRight);
    std::cout << "Text bounding box: (" << bottomLeft.first << ", " << bottomLeft.second
              << ") - (" << topRight.first << ", " << topRight.second << ")" << std::endl;
}

void TextShape::setBoundingBox(Coordinate t1, Coordinate t2) {
    std::cout << "Bounding box updated to new coordinates." << std::endl;
}

std::unique_ptr<Manipulator> TextShape::createManipulator() const {
    return std::make_unique<Manipulator>();
}

void TextShape::giveDescription() const {
    std::cout << "This is an adapted text shape: \"" << textView_->getText() << "\"" << std::endl;
}
