#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

/*
    Time Complexity: O(n ^ 3)
    Space Complexity: O(n ^ 2)
*/
std::vector<std::vector<double>> inverse(const std::vector<std::vector<double>>& matrix) {
    if (matrix.size() != matrix[0].size()) {
        throw std::runtime_error("Not a square matrix");
    }
    
    int n = matrix.size();
    std::vector<std::vector<double>> aug(n, std::vector<double>(2 * n, 0.0));

    // augmented matrix [matrix | identity]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            aug[i][j] = matrix[i][j];
        }

        aug[i][n + i] = 1.0;
    }

    // Gaussian elimination
    for (int i = 0; i < n; ++i) {
        double pivot = aug[i][i];
        if (pivot == 0.0) {
            int swap_row = -1;
            for (int j = i + 1; j < n; ++j) {
                if (aug[j][i] != 0.0) {
                    swap_row = j;
                    break;
                }
            }
        
            if (swap_row == -1) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
        
            std::swap(aug[i], aug[swap_row]);
            pivot = aug[i][i];
        }

        for (int j = 0; j < 2 * n; ++j) {
            aug[i][j] /= pivot;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = aug[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    aug[k][j] -= factor * aug[i][j];
                }
            }
        }
    }

    // extract inverse matrix
    std::vector<std::vector<double>> inv(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv[i][j] = aug[i][n + j];
        }
    }

    return inv;
}
