#include <cmath>
#include <vector>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace hw {

/* 
    Recursive approach 
    Time Complexity: O(2 ^ n) 
    Space Complexity: O(n) 
*/
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
std::size_t fib_recursive(const T& n) {
    if (n < 0) {
        throw std::invalid_argument("fib_recursive: Fibonacci sequence is only defined for non-negative integers.");
    }
    if (n <= 1) {
        return n;
    }

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

/* 
    Iterative approach 
    Time Complexity: O(n) 
    Space Complexity: O(1) 
*/
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
std::size_t fib_iterative(const T& n) {
    if (n < 0) {
        throw std::invalid_argument("fib_iterative: Fibonacci sequence is only defined for non-negative integers.");
    }
    if (n <= 1) {
        return n;
    }

    std::size_t a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        std::size_t next = a + b;
        a = b;
        b = next;
    }

    return b;
}

/* 
    Dynamic Programming approach 
    Time Complexity: O(n) 
    Space Complexity: O(n) 
*/
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
std::size_t fib_dp(const T& n) {
    if (n < 0) {
        throw std::invalid_argument("fib_dp: Fibonacci sequence is only defined for non-negative integers.");
    }

    if (n <= 1) {
        return n;
    }

    std::vector<std::size_t> dp{0, 1};
    for (std::size_t i = 2; i <= n; ++i) {
        dp.push_back(dp[i - 1] + dp[i - 2]);
    }

    return dp.back();
}

/* 
    Binet's formula 
    Time Complexity: O(log(n)) || O(1) (Practically) 
    Space Complexity: O(1) 
*/
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
std::size_t fib_Binet(const T& n) {
    if (n < 0) {
        throw std::invalid_argument("fib_Binet: Fibonacci sequence is only defined for non-negative integers.");
    }

    const long double phi = (1 + std::sqrt(5.0L)) / 2.0L;
    const long double psi = (1 - std::sqrt(5.0L)) / 2.0L;
    long double value = (std::pow(phi, n) - std::pow(psi, n)) / std::sqrt(5.0L) + 0.5L;

    return static_cast<std::size_t>(std::round(value));
}

/*
    Time complexity: O(1)
    Space complexity: O(1)
*/
std::vector<std::vector<std::size_t>> matrix_multiply(const std::vector<std::vector<std::size_t>>& A,
                                                      const std::vector<std::vector<std::size_t>>& B) {
    return {
        {
            A[0][0] * B[0][0] + A[0][1] * B[1][0],
            A[0][0] * B[0][1] + A[0][1] * B[1][1]
        },
        {
            A[1][0] * B[0][0] + A[1][1] * B[1][0],
            A[1][0] * B[0][1] + A[1][1] * B[1][1]
        }
    };
}

/*
    Time complexity: O(log(n))
*/
std::vector<std::vector<std::size_t>> matrix_power(std::vector<std::vector<std::size_t>> base, std::size_t exp) {
    std::vector<std::vector<std::size_t>> result{{1, 0}, {0, 1}};

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matrix_multiply(result, base);
        }

        base = matrix_multiply(base, base);
        exp /= 2;
    }

    return result;
}

/*
    Matrix Approach
    Time Complexity: O(log(n))
    Space Complexity: O(1)
*/
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
std::size_t fib_matrix(const T& n) {
    if (n < 0) {
        throw std::invalid_argument("fib_matrix: Fibonacci sequence is only defined for non-negative integers.");
    }

    if (n <= 1) {
        return n;
    }

    std::vector<std::vector<std::size_t>> A{{1, 1}, {1, 0}};
    auto result = matrix_power(A, n - 1);

    return result[0][0];
}

} // namespace hw
