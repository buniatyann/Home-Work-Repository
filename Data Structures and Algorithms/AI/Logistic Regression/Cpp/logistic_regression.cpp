#include <vector>
#include <type_traits>
#include <cmath>
#include <stdexcept>

/**
 * @brief Type trait to ensure the template type is numeric.
 * @tparam T The type to check.
 */
template<typename T>
using is_numeric = std::enable_if_t<std::is_arithmetic<T>::value>;

/**
 * @brief Adds a bias term (1) to each row of the input matrix.
 * @tparam T Numeric type of the matrix elements.
 * @param X Input feature matrix.
 * @return Matrix with a bias term prepended to each row.
 * @throws std::invalid_argument If the input matrix is empty.
 */
template<typename T, typename = is_numeric<T>>
std::vector<std::vector<T>> add_bias_term(const std::vector<std::vector<T>>& X) {
    if (X.empty() || X[0].empty()) {
        throw std::invalid_argument("add_bias_term: input matrix cannot be empty");
    }

    std::vector<std::vector<T>> X_b(X.size());
    for (size_t i = 0; i < X.size(); ++i) {
        X_b[i].reserve(X[i].size() + 1);
        X_b[i].push_back(T(1));  // Bias term
        X_b[i].insert(X_b[i].end(), X[i].begin(), X[i].end());
    }
    
    return X_b;
}


/**
 * @brief Transposes a matrix.
 * @tparam T Numeric type of the matrix elements.
 * @param matrix Input matrix to transpose.
 * @return Transposed matrix.
 * @throws std::invalid_argument If the input matrix is empty.
 */
template<typename T, typename = is_numeric<T>>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("transpose: matrix cannot be empty");
    }
    
    std::vector<std::vector<T>> result(matrix[0].size(), std::vector<T>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    
    return result;
}

/**
 * @brief Performs vector-matrix multiplication.
 * @tparam T Numeric type of the matrix and vector elements.
 * @param X Input matrix.
 * @param theta Input vector (parameters).
 * @return Resulting vector from the multiplication.
 * @throws std::invalid_argument If the matrix is empty or dimensions are incompatible.
 */
template<typename T, typename = is_numeric<T>>
std::vector<T> matrix_vector_multiply(const std::vector<std::vector<T>>& X, const std::vector<T>& theta) {
    if (X.empty() || X[0].empty()) {
        throw std::invalid_argument("matrix_vector_multiply: matrix cannot be empty");
    }
    if (X[0].size() != theta.size()) {
        throw std::invalid_argument("matrix_vector_multiply: incompatible dimensions");
    }
    
    std::vector<T> result(X.size(), T(0));
    for (size_t i = 0; i < X.size(); ++i) {
        for (size_t j = 0; j < X[0].size(); ++j) {
            result[i] += X[i][j] * theta[j];
        }
    }
    
    return result;
}

/**
 * @brief Applies the sigmoid function to each element of a vector.
 * @tparam T Numeric type of the vector elements.
 * @param vec Input vector.
 * @return Vector with sigmoid applied to each element.
 * @throws std::invalid_argument If the input vector is empty.
 */
template<typename T, typename = is_numeric<T>>
std::vector<T> sigmoid(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("sigmoid: argument must be a non-empty vector");
    }
    
    std::vector<T> ans(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        ans[i] = T(1) / (T(1) + std::exp(-vec[i]));
    }
    
    return ans;
}

/**
 * @brief Computes the logistic regression cost function (binary cross-entropy).
 * @tparam T Numeric type of the vector elements.
 * @param h Predicted probabilities.
 * @param y True labels.
 * @return Average cost over all samples.
 * @throws std::invalid_argument If inputs are empty or have different sizes.
 */
template<typename T, typename = is_numeric<T>>
T cost_function(const std::vector<T>& h, const std::vector<T>& y) {
    if (h.empty() || y.empty()) {
        throw std::invalid_argument("cost_function: both arguments must be non-empty");
    }
    if (h.size() != y.size()) {
        throw std::invalid_argument("cost_function: arguments must have equal size");
    }
    
    T sum = T(0);
    for (size_t i = 0; i < y.size(); ++i) {
        // Add small epsilon to avoid log(0)
        constexpr T epsilon = T(1e-10);
        sum += -y[i] * std::log(h[i] + epsilon) - (T(1) - y[i]) * std::log(T(1) - h[i] + epsilon);
    }
    
    return sum / static_cast<T>(y.size());
}

/**
 * @brief Predicts probabilities using logistic regression.
 * @tparam T Numeric type of the matrix and vector elements.
 * @param X Input feature matrix.
 * @param theta Parameter vector (including bias term).
 * @return Vector of predicted probabilities.
 * @throws std::invalid_argument If the input matrix is empty or dimensions are incompatible.
 */
template<typename T, typename = is_numeric<T>>
std::vector<T> predict_prob(const std::vector<std::vector<T>>& X, const std::vector<T>& theta) {
    if (X.empty() || X[0].empty()) {
        throw std::invalid_argument("predict_prob: input matrix cannot be empty");
    }
    if (X[0].size() + 1 != theta.size()) {
        throw std::invalid_argument("predict_prob: incompatible dimensions");
    }
    
    // Add bias term
    std::vector<std::vector<T>> X_b = add_bias_term(X);
    std::vector<T> mult = matrix_vector_multiply(X_b, theta);
    
    return sigmoid(mult);
}

/**
 * @brief Converts probabilities to binary predictions based on a threshold.
 * @tparam T Numeric type of the matrix and vector elements.
 * @param X Input feature matrix.
 * @param theta Parameter vector (including bias term).
 * @param threshold Classification threshold (default: 0.5).
 * @return Vector of boolean predictions.
 * @throws std::invalid_argument If the input matrix is empty, dimensions are incompatible, or threshold is invalid.
 */
template<typename T, typename = is_numeric<T>>
std::vector<bool> prob(const std::vector<std::vector<T>>& X, const std::vector<T>& theta, T threshold = T(0.5)) {
    if (threshold < T(0) || threshold > T(1)) {
        throw std::invalid_argument("prob: threshold must be between 0 and 1");
    }
    
    std::vector<T> probabilities = predict_prob(X, theta);
    std::vector<bool> ans(probabilities.size());
    for (size_t i = 0; i < probabilities.size(); ++i) {
        ans[i] = (probabilities[i] >= threshold);
    }
    
    return ans;
}

/**
 * @brief Trains a logistic regression model using gradient descent.
 * @tparam T Numeric type of the matrix and vector elements.
 * @param X Input feature matrix.
 * @param y True labels.
 * @param num_iterations Number of gradient descent iterations.
 * @param learning_rate Learning rate for gradient descent.
 * @return Trained parameter vector (including bias term).
 * @throws std::invalid_argument If inputs are empty, dimensions are incompatible, or parameters are invalid.
 */
template<typename T, typename = is_numeric<T>>
std::vector<T> logistic_regression(std::vector<std::vector<T>>& X, std::vector<T>& y, int num_iterations, T learning_rate) {
    if (X.empty() || X[0].empty() || y.empty()) {
        throw std::invalid_argument("logistic_regression: inputs cannot be empty");
    }
    if (X.size() != y.size()) {
        throw std::invalid_argument("logistic_regression: X and y must have same number of rows");
    }
    if (num_iterations <= 0) {
        throw std::invalid_argument("logistic_regression: number of iterations must be positive");
    }
    if (learning_rate <= T(0)) {
        throw std::invalid_argument("logistic_regression: learning rate must be positive");
    }
    
    // Add bias term
    std::vector<std::vector<T>> X_b = add_bias_term(X);
    
    // Initialize theta with zeros (more stable than ones)
    std::vector<T> theta(X_b[0].size(), T(0));
    
    for (int i = 0; i < num_iterations; ++i) {
        std::vector<T> z = matrix_vector_multiply(X_b, theta);
        std::vector<T> h = sigmoid(z);
        
        // Calculate gradient
        std::vector<T> errors(h.size());
        for (size_t j = 0; j < h.size(); ++j) {
            errors[j] = h[j] - y[j];
        }
        
        std::vector<std::vector<T>> X_b_T = transpose(X_b);
        std::vector<T> gradient = matrix_vector_multiply(X_b_T, errors);
        
        // Update theta
        for (size_t j = 0; j < theta.size(); ++j) {
            theta[j] -= learning_rate * gradient[j] / static_cast<T>(X.size());
        }
        
        // if (i % 100 == 0) {
        //     T loss = cost_function(h, y);
        //     std::cout << "Iteration " << i << " - Loss: " << loss << "\n";
        // }
    }
    
    return theta;
}