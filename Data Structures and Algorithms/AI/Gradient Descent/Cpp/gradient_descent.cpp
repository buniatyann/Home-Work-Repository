#include <vector>
#include <tuple>
#include <stdexcept>
#include <cmath>
#include <type_traits>

/**
 * @brief Multiplies a matrix with a vector.
 * 
 * @tparam T Numeric type.
 * @param X The input matrix (2D vector).
 * @param v The input vector.
 * @return std::vector<T> Resulting vector after multiplication.
 * @throws std::invalid_argument if dimensions are incompatible or inputs are empty.
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::vector<T> matrix_vector_multiply(const std::vector<std::vector<T>>& X, 
                                      const std::vector<T>& v) {
    if (X.empty() || X[0].empty() || v.empty()) {
        throw std::invalid_argument("Empty matrix or vector in matrix_vector_multiply");
    }
    if (X[0].size() != v.size()) {
        throw std::invalid_argument("Incompatible dimensions in matrix_vector_multiply");
    }
    
    std::vector<T> result(X.size(), T(0));
    for (size_t i = 0; i < X.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            result[i] += X[i][j] * v[j];
        }
    }
    return result;
}

/**
 * @brief Subtracts one vector from another.
 * 
 * @tparam T Numeric type.
 * @param a First vector.
 * @param b Second vector.
 * @return std::vector<T> The result of a - b.
 * @throws std::invalid_argument if vector sizes do not match.
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::vector<T> vector_subtract(const std::vector<T>& a, 
                               const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Incompatible vector sizes in vector_subtract");
    }

    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }

    return result;
}

/**
 * @brief Transposes a matrix.
 * 
 * @tparam T Numeric type.
 * @param X The input matrix.
 * @return std::vector<std::vector<T>> Transposed matrix.
 * @throws std::invalid_argument if input matrix is empty.
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& X) {
    if (X.empty() || X[0].empty()) {
        throw std::invalid_argument("Empty matrix in transpose");
    }

    size_t rows = X.size(), cols = X[0].size();
    std::vector<std::vector<T>> result(cols, std::vector<T>(rows));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = X[i][j];
        }
    }

    return result;
}

/**
 * @brief Computes the mean squared error cost.
 * 
 * @tparam T Numeric type.
 * @param X Input features matrix.
 * @param y Actual output values.
 * @param theta Model parameters.
 * @return T Mean squared error.
 * @throws std::invalid_argument if dimensions are invalid.
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
T cost(const std::vector<std::vector<T>>& X, 
       const std::vector<T>& y, 
       const std::vector<T>& theta) {
    if (X.empty() || X[0].empty() || y.empty() || theta.empty()) {
        throw std::invalid_argument("Empty input in cost function");
    }
    if (X.size() != y.size() || X[0].size() != theta.size()) {
        throw std::invalid_argument("Incompatible dimensions in cost function");
    }

    std::vector<T> predictions = matrix_vector_multiply(X, theta);
    T sum = T(0);
    for (size_t i = 0; i < predictions.size(); ++i) {
        sum += std::pow(predictions[i] - y[i], 2);
    }

    return sum / static_cast<T>(X.size());
}

/**
 * @brief Performs gradient descent optimization.
 * 
 * @tparam T Numeric type.
 * @param X Input features matrix (with bias column).
 * @param y Target output vector.
 * @param theta Initial model parameters (modifiable).
 * @param alpha Learning rate.
 * @param iterations Number of iterations to run.
 * @return std::tuple<std::vector<T>, std::vector<T>, std::vector<std::vector<T>>> 
 *         A tuple containing the final theta, cost history, and theta history per iteration.
 * @throws std::invalid_argument if input validation fails.
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::tuple<std::vector<T>, std::vector<T>, std::vector<std::vector<T>>> 
gradient_descent(const std::vector<std::vector<T>>& X, 
                 const std::vector<T>& y, 
                 std::vector<T> theta, 
                 T alpha, 
                 int iterations) {
    if (X.empty() || X[0].empty() || y.empty() || theta.empty()) {
        throw std::invalid_argument("Empty input in gradient_descent");
    }
    if (X.size() != y.size() || X[0].size() != theta.size()) {
        throw std::invalid_argument("Incompatible dimensions in gradient_descent");
    }
    if (iterations <= 0) {
        throw std::invalid_argument("Iterations must be positive");
    }
    if (alpha <= T(0)) {
        throw std::invalid_argument("Learning rate alpha must be positive");
    }

    size_t m = X.size();
    std::vector<T> cost_history(iterations);
    std::vector<std::vector<T>> theta_history(iterations, std::vector<T>(theta.size()));

    for (int i = 0; i < iterations; ++i) {
        std::vector<T> prediction = matrix_vector_multiply(X, theta);
        std::vector<T> error = vector_subtract(prediction, y);

        std::vector<std::vector<T>> X_T = transpose(X);
        std::vector<T> gradient = matrix_vector_multiply(X_T, error);

        for (size_t j = 0; j < theta.size(); ++j) {
            theta[j] -= (alpha / static_cast<T>(m)) * gradient[j];
        }

        theta_history[i] = theta;
        cost_history[i] = cost(X, y, theta);
    }

    return std::make_tuple(theta, cost_history, theta_history);
}
