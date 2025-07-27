#include <vector>
#include <random>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

/**
 * @brief Computes the dot product between two vectors.
 * 
 * @tparam T Numeric type.
 * @param a Vector a.
 * @param b Vector b.
 * @return Dot product of a and b.
 * @throws std::invalid_argument if vector sizes do not match.
 */
template<typename T>
T dot_product(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be the same length for dot product.");
    }

    T result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    
    return result;
}

/**
 * @brief Returns the transpose of a matrix.
 * 
 * @tparam T Numeric type.
 * @param matrix Input matrix.
 * @return Transposed matrix.
 * @throws std::invalid_argument if input matrix is empty or rows are inconsistent.
 */
template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("Cannot transpose an empty matrix.");
    }

    std::size_t cols = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != cols) {
            throw std::invalid_argument("Inconsistent row lengths in matrix.");
        }
    }

    std::vector<std::vector<T>> result(cols, std::vector<T>(matrix.size()));
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

/**
 * @brief Performs mini-batch gradient descent for linear regression.
 * 
 * @tparam T Numeric type (e.g., float, double).
 * @param X Feature matrix of shape (m x n).
 * @param y Target vector of shape (m).
 * @param learning_rate Learning rate for updates.
 * @param batch_size Number of samples per batch.
 * @param epochs Number of iterations over the data.
 * @return Optimized parameter vector theta (size n).
 * @throws std::invalid_argument if inputs are invalid.
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, std::vector<T>>::type
gradient_descent(const std::vector<std::vector<T>>& X, const std::vector<T>& y,
                 T learning_rate = 0.01, size_t batch_size = 16, std::size_t epochs = 100) {
    if (X.empty() || X[0].empty()) {
        throw std::invalid_argument("Feature matrix X must not be empty.");
    }
    if (X.size() != y.size()) {
        throw std::invalid_argument("X and y must have the same number of samples.");
    }

    std::size_t m = X.size();
    std::size_t n = X[0].size();

    for (const auto& row : X) {
        if (row.size() != n) {
            throw std::invalid_argument("All rows in X must have the same number of columns.");
        }
    }

    std::vector<T> theta(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(-1, 1);
    for (T& t : theta) {
        t = dist(gen);
    }

    for (std::size_t epoch = 0; epoch < epochs; ++epoch) {
        std::vector<std::size_t> indices(m);
        for (std::size_t i = 0; i < m; ++i) {
            indices[i] = i;
        }
        
        std::shuffle(indices.begin(), indices.end(), gen);
        for (size_t i = 0; i < m; i += batch_size) {
            std::size_t end = std::min(i + batch_size, m);
            std::size_t actual_batch = end - i;
            std::vector<T> gradient(n, 0);
            for (std::size_t j = i; j < end; ++j) {
                std::size_t idx = indices[j];
                T pred = dot_product(X[idx], theta);
                T error = pred - y[idx];
                for (std::size_t k = 0; k < n; ++k) {
                    gradient[k] += error * X[idx][k];
                }
            }

            for (std::size_t k = 0; k < n; ++k) {
                theta[k] -= learning_rate * (2.0 / actual_batch) * gradient[k];
            }
        }
    }

    return theta;
}
