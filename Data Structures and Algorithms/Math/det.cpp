#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

/*
    Computing the determinant of a square matrix using LU decomposition with partial pivoting.
    Time Complexity: O(n^3)
    Space Complexity: O(n^2)
*/
long double determinant_lu(const std::vector<std::vector<long double>>& matrix) {
    if (matrix.empty()) {
        throw std::runtime_error("Matrix is empty");
    }

    std::size_t n = matrix.size();
    if (n != matrix[0].size()) {
        throw std::runtime_error("Matrix should be square");
    }

    // Check all rows have the same size
    for (const auto& row : matrix) {
        if (row.size() != n) {
            throw std::runtime_error("All rows must have the same size");
        }
    }

    std::vector<std::vector<long double>> A(matrix);
    int8_t sign = 1;

    for (std::size_t i = 0; i < n; ++i) {
        // pivoting
        std::size_t max_row = i;
        for (std::size_t k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                max_row = k;
            }
        }

        // if pivot is effectively zero, determinant is 0
        if (std::abs(A[max_row][i]) < 1e-10) {
            return 0.0;
        }

        // swap rows if needed
        if (i != max_row) {
            std::swap(A[i], A[max_row]);
            sign *= -1;
        }

        // elimination
        for (std::size_t j = i + 1; j < n; ++j) {
            long double factor = A[j][i] / A[i][i];
            for (std::size_t k = i; k < n; ++k) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    long double det = sign;
    for (std::size_t i = 0; i < n; ++i) {
        det *= A[i][i];
    }

    return det;
}