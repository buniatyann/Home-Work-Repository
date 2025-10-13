// #include "Point.hpp"
// #include "Vector.hpp"
#include "Coord.hpp"
#include <iostream>


int main() {
    coord_t<double> x;
    coord_t<double> y;

    std::cout << (x < y) << std::endl;

    return 0;
}