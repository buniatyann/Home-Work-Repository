#include <vector>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <iomanip>
#include <type_traits>

/// @brief Struct representing the result of a linear regression
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct LinearModel {
    T slope;
    T intercept;
    T r_squared;
};

/// @brief Computes the mean of a vector
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
T mean(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("mean: input vector is empty");
    }
    
    T sum = std::accumulate(vec.begin(), vec.end(), T(0));
    return sum / vec.size();
}

/// @brief Computes simple linear regression y = m*x + c and R² score
/// @param x vector of independent variables
/// @param y vector of dependent variables
/// @return LinearModel struct containing slope (m), intercept (c), and R²
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
LinearModel<T> simple_linear_regression(const std::vector<T>& x, const std::vector<T>& y) {
    std::size_t n = x.size();

    if (n == 0 || y.size() == 0) {
        throw std::invalid_argument("Input vectors must not be empty.");
    }
    if (n != y.size()) {
        throw std::invalid_argument("Input vectors must have the same length.");
    }

    T mean_x = mean(x);
    T mean_y = mean(y);

    T numerator = 0;
    T denominator = 0;
    T total_variance = 0;
    T explained_variance = 0;

    for (std::size_t i = 0; i < n; ++i) {
        T dx = x[i] - mean_x;
        T dy = y[i] - mean_y;
        
        numerator += dx * dy;
        denominator += dx * dx;
    }

    if (denominator == T(0)) {
        throw std::runtime_error("Slope is undefined: all x values are equal.");
    }

    T m = numerator / denominator;
    T c = mean_y - m * mean_x;

    // Compute R² (coefficient of determination)
    for (std::size_t i = 0; i < n; ++i) {
        T y_pred = m * x[i] + c;
        T residual = y[i] - y_pred;
        explained_variance += residual * residual;
        T total_diff = y[i] - mean_y;
        total_variance += total_diff * total_diff;
    }

    T r2 = T(1) - (explained_variance / total_variance);

    return {m, c, r2};
}