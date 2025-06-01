#include <cmath>

/*
    requires C++ 20, and defined in <numbers>
    constexpr double Eu = std::numbers::e;
*/
double softplus(double x) {
    return std::log1p(std::exp(x));  // is the same as log(1 + exp(x)) and numerically stable
}
