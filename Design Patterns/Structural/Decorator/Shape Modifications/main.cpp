#include <iostream>
#include <memory>
#include "include/Shapes/Triangle.hpp"
#include "include/Shapes/Rectangle.hpp"
#include "include/Shapes/Circle.hpp"
#include "include/Decorators/ColoredShapeDecorator.hpp"

int main() {
    std::cout << "Choose a shape to draw:\n";
    std::cout << "1. Triangle\n";
    std::cout << "2. Rectangle\n";
    std::cout << "3. Circle\n";
    std::cout << "Enter your choice (1/2/3): ";
    int shapeChoice;
    std::cin >> shapeChoice;

    std::unique_ptr<IShape> shape;

    switch(shapeChoice) {
        case 1:
            shape = std::make_unique<Triangle>();
            break;
        case 2:
            shape = std::make_unique<Rectangle>();
            break;
        case 3:
            shape = std::make_unique<Circle>();
            break;
        default:
            std::cout << "Invalid choice, defaulting to Triangle." << std::endl;
            shape = std::make_unique<Triangle>();
            break;
    }

    std::cout << "\nWould you like to add color to the shape? (y/n): ";
    char colorChoice;
    std::cin >> colorChoice;

    if (colorChoice == 'y' || colorChoice == 'Y') {
        std::cout << "Enter color: ";
        std::string color;
        std::cin >> color;

        shape = std::make_unique<ColoredShapeDecorator>(std::move(shape), color);
    }

    std::cout << "\nShape Information:\n";
    shape->info();
    std::cout << "\nShape Drawing:\n";
    shape->draw();

    return 0;
}
