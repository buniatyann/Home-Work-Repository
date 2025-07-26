#include <vector>
#include <random>
#include <type_traits>
#include <utility>

/**
 * @brief Performs stochastic gradient descent for univariate linear regression.
 *
 * @tparam T Arithmetic type (e.g., float, double).
 * @param X Input feature vector.
 * @param Y Target output vector.
 * @param learning_rate Learning rate for gradient updates.
 * @param epochs Number of iterations for the SGD loop.
 * @return std::pair<T, T> A pair containing the learned slope (m) and intercept (b).
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, std::pair<T, T>>::type
stochastic_gradient_descent(const std::vector<T>& X, const std::vector<T>& Y, T learning_rate, int epochs) {
    if (X.size() != Y.size() || X.empty()) {
        throw std::invalid_argument("Input vectors must be non-empty and of equal length.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(-1.0, 1.0);

    T m = dist(gen);
    T b = dist(gen);

    for (int i = 0; i < epochs; ++i) {
        std::size_t idx = std::rand() % X.size();
        T x = X[idx];
        T y = Y[idx];
        T pred = m * x + b;
        T grad_m = (pred - y) * x;
        T grad_b = (pred - y);
        m -= learning_rate * grad_m;
        b -= learning_rate * grad_b;
    }

    return {m, b};
}
