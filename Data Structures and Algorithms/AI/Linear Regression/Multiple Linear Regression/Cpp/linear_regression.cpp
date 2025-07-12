#include <vector>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <tuple>

/// @brief Adds a column of 1s at the beginning of the matrix X
/// @param X Input matrix (n x k)
/// @return New matrix (n x (k+1)) with a column of 1s as the first column
std::vector<std::vector<double>> add_intercept_column(const std::vector<std::vector<double>>& X) {
    if (X.empty()) {
        throw std::invalid_argument("Input matrix X is empty");
    }

    size_t n = X.size();
    size_t k = X[0].size();
    for (const auto& row : X) {
        if (row.size() != k) {
            throw std::invalid_argument("All rows in X must have the same number of columns");
        }
    }

    std::vector<std::vector<double>> result(n, std::vector<double>(k + 1, 0.0));
    for (size_t i = 0; i < n; ++i) {
        result[i][0] = 1.0; // Set first column to 1
        for (size_t j = 0; j < k; ++j) {
            result[i][j + 1] = X[i][j]; // Copy original elements
        }
    }
    
    return result;
}

/// @brief Computes matrix-vector multiplication: result = A * x
std::vector<double> matrix_vector_multiply(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    if (cols != x.size()) {
        throw std::invalid_argument("Matrix-vector dimensions mismatch");
    }

    std::vector<double> result(rows, 0.0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }

    return result;
}

/// @brief Computes matrix multiplication: result = A * B
std::vector<std::vector<double>> matrix_multiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    size_t rows_A = A.size();
    size_t cols_A = A[0].size();
    size_t rows_B = B.size();
    size_t cols_B = B[0].size();
    if (cols_A != rows_B) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }

    std::vector<std::vector<double>> result(rows_A, std::vector<double>(cols_B, 0.0));
    for (size_t i = 0; i < rows_A; ++i) {
        for (size_t j = 0; j < cols_B; ++j) {
            for (size_t k = 0; k < cols_A; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return result;
}

/// @brief Computes matrix transpose
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& A) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    std::vector<std::vector<double>> result(cols, std::vector<double>(rows, 0.0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = A[i][j];
        }
    }
    
    return result;
}

/// @brief Computes inverse of a square matrix using Gaussian elimination
std::vector<std::vector<double>> matrix_inverse(const std::vector<std::vector<double>>& A) {
    size_t n = A.size();
    if (n == 0 || A[0].size() != n) {
        throw std::invalid_argument("Matrix must be square for inversion");
    }

    // Create augmented matrix [A|I]
    std::vector<std::vector<double>> aug(n, std::vector<double>(2 * n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            aug[i][j] = A[i][j];
        }
        aug[i][i + n] = 1.0; // Identity matrix part
    }

    // Gaussian elimination with partial pivoting
    for (size_t i = 0; i < n; ++i) {
        // Find pivot
        double max_val = std::abs(aug[i][i]);
        size_t max_row = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(aug[k][i]) > max_val) {
                max_val = std::abs(aug[k][i]);
                max_row = k;
            }
        }
    
        if (max_val == 0.0) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        if (max_row != i) {
            std::swap(aug[i], aug[max_row]);
        }

        // Make pivot 1
        double pivot = aug[i][i];
        for (size_t j = 0; j < 2 * n; ++j) {
            aug[i][j] /= pivot;
        }

        // Eliminate column
        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                double factor = aug[k][i];
                for (size_t j = 0; j < 2 * n; ++j) {
                    aug[k][j] -= factor * aug[i][j];
                }
            }
        }
    }

    // Extract inverse
    std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            inverse[i][j] = aug[i][j + n];
        }
    }
    
    return inverse;
}

/// @brief Computes multiple linear regression coefficients and metrics
/// @param X Matrix of independent variables (n x k, including column of ones for intercept)
/// @param y Vector of dependent variables (n x 1)
/// @return Tuple containing (coefficients, R², SS_res)
std::tuple<std::vector<double>, double, double> multiple_linear_regression(const std::vector<std::vector<double>>& X, const std::vector<double>& y) {
    // Input validation
    if (X.empty() || y.empty()) {
        throw std::invalid_argument("Input matrix X or vector y is empty");
    }
    
    size_t n = X.size();
    if (n != y.size()) {
        throw std::invalid_argument("Number of rows in X must match length of y");
    }
    if (X[0].empty()) {
        throw std::invalid_argument("X matrix has no columns");
    }
    
    size_t k = X[0].size();
    for (const auto& row : X) {
        if (row.size() != k) {
            throw std::invalid_argument("All rows in X must have the same number of columns");
        }
    }

    // Compute X^T * X
    auto Xt = transpose(X);
    auto XtX = matrix_multiply(Xt, X);

    // Compute X^T * y
    std::vector<double> Xty(k, 0.0);
    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < n; ++j) {
            Xty[i] += Xt[i][j] * y[j];
        }
    }

    // Compute coefficients: beta = (X^T * X)^(-1) * (X^T * y)
    auto XtX_inv = matrix_inverse(XtX);
    auto beta = matrix_vector_multiply(XtX_inv, Xty);

    // Compute predicted values: y_pred = X * beta
    auto y_pred = matrix_vector_multiply(X, beta);

    // Compute mean of y
    double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

    // Compute SS_res (sum of squared residuals)
    double ss_res = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double residual = y[i] - y_pred[i];
        ss_res += residual * residual;
    }

    // Compute SS_tot (total sum of squares)
    double ss_tot = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double diff = y[i] - mean_y;
        ss_tot += diff * diff;
    }

    // Compute R²
    double r_squared = (ss_tot != 0.0) ? 1.0 - (ss_res / ss_tot) : 1.0;

    // Return tuple: (coefficients, R², SS_res)
    return std::make_tuple(beta, r_squared, ss_res);
}