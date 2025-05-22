#include "include/calculator/calculator.hpp"
#include <iostream>


int main() {
    calculator calc;
    std::string expr;
    std::cout << "Enter expressions \n";
    std::cout << "Press Enter with an empty line to exit.\n";

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, expr);
 
        if (expr.empty()) {
            std::cout << "Exiting...\n";
            break;
        }

        try {
            double result = calc.evaluate_expression(expr);
            std::cout << result << std::endl;
        } catch (const calculator_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}