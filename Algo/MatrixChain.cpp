#include <vector>
#include <iostream>
#include <string>
#include <climits>
#include <limits>
#include <type_traits>
#include <stdexcept>

template <typename T>
void optimalParenthesisPrint(const std::vector<std::vector<T>>& s, std::size_t i, std::size_t j) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type.");

    if (i == j) {
        std::cout << "A" << i;
    } 
    else {
        std::cout << "(";
        optimalParenthesisPrint(s, i, s[i][j]);
        optimalParenthesisPrint(s, s[i][j] + 1, j);
        std::cout << ")";
    }
}

/*
    p = {1, 2, 3, 4} =>:
        dim(A1) = 1 x 2
        dim(A2) = 2 x 3
        dim(A3) = 3 x 4
*/
template <typename T>
std::pair<T, std::vector<std::vector<T>>> matrixChainOrder(const std::vector<T>& p) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type.");

    std::size_t n = p.size() - 1; // number of matrices
    if (n == 0) {
        throw std::invalid_argument("At least one matrix required.");
    }

    std::vector<std::vector<T>> m(n + 1, std::vector<T>(n + 1, 0));
    std::vector<std::vector<T>> s(n + 1, std::vector<T>(n + 1, 0));

    for (std::size_t chain_len = 2; chain_len <= n; ++chain_len) {
        for (std::size_t i = 1; i <= n - chain_len + 1; ++i) {
            std::size_t j = i + chain_len - 1;
            m[i][j] = std::numeric_limits<T>::max();
            for (std::size_t k = i; k < j; ++k) {
                T cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = static_cast<T>(k); // safe if k fits in T
                }
            }
        }
    }

    return {m[1][n], s};
}
