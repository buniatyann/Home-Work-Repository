#include "IGraphObject.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Group.hpp"
#include <memory>
#include <iostream>

int main() {
    Group root;

    root.addObject(std::make_unique<Rectangle>());
    root.addObject(std::make_unique<Circle>());

    Group subgroup;
    subgroup.addObject(std::make_unique<Triangle>());
    subgroup.addObject(std::make_unique<Circle>());

    root.addObject(std::make_unique<Group>(std::move(subgroup)));
    root.addObject(std::make_unique<Triangle>());

    std::cout << "Drawing the entire hierarchy:\n";
    root.draw();

    return 0;
}