#include "TextShape.hpp"

int main() {
    auto textView = std::make_unique<TextView>("Hello Adapter", std::make_pair(0.0, 0.0), std::make_pair(10.0, 5.0));
    TextShape textShape(std::move(textView));

    textShape.boundingBox();
    textShape.giveDescription();
    textShape.createManipulator()->print();

    return 0;
}
