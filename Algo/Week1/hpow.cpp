#include <stdexcept>
#include <random>
#include <type_traits>
#include <cmath>

namespace hw {
    /*
        Iterative approach 
        Time Complexity: O(log(n))
        Space Complexity: O(1)
    */
    long double pow(double x, int m) {
        if (x == 0 && m <= 0) {
            throw std::invalid_argument("Indeterminate form: 0^0 or division by zero.");
        }

        bool neg_exp = (m < 0); // sign 
        // long long exp = std::abs(static_cast<long long>(m)); ??
        int exp = std::abs(m); 
        long double base = static_cast<long double>(x);
        long double res = 1.0;
        
        while (exp > 0) {
            if (exp % 2 == 1) {
                res *= base;
            }

            base *= base;
            exp /= 2;
        }

        return neg_exp ? 1.0 / res : res;
    }


    template <typename BaseType, typename ExpType> 
    long double hpow(BaseType base, ExpType exponent) {
        if constexpr (!std::is_arithmetic<BaseType>::value) {
            throw std::invalid_argument("hpow_iterative: BaseType must be numeric (int, double, float, etc.)");
        }
        if constexpr (!std::is_integral<ExpType>::value) {
            throw std::invalid_argument("hpow_iterative: ExpType must be an integer type");
        }

        if (base == 0 && exponent <= 0) {
            throw std::invalid_argument("hpow_iterative: Indeterminate form: 0^0 or division by zero.");
        }

        bool neg_exp = (exponent < 0);
        ExpType exp = std::abs(exponent);
        long double a = static_cast<long double>(base);
        long double res = 1.0;

        while (exp > 0) {
            if (exp % 2 == 1) {
                res *= a;
            }
            
            a *= a;
            exp /= 2;
        }

        return neg_exp ? 1.0 / res : res;
    }

    /*
        Recursive approach 
        Time Complexity: O(log(n))
        Space Complexity: O(log(n))
    */
    long double hpow_recursive_helper(long double base, int exp) {
        if (exp == 0) {
            return 1.0;
        }
        if (exp == 1) {
            return base;
        }

        long double half = hpow_recursive_helper(base * base, exp / 2);
        return (exp % 2 == 0) ? half : base * half;
    }

    long double hpow_recursive(double base, int exponent) {
        if (base == 0 && exponent <= 0) {
            throw std::invalid_argument("hpow_recursive: Indeterminate form: 0^0 or division by zero.");
        }

        bool neg_exp = (exponent < 0);
        int abs_exp = std::abs(exponent);
        long double base_ld = static_cast<long double>(base);
        long double result = hpow_recursive_helper(base_ld, abs_exp);

        return neg_exp ? 1.0 / result : result;
    }

    template <typename BaseType, typename ExpType>
    long double hpow_recursive_impl(long double base, ExpType exp) {
        if (exp == 0) {
            return 1.0;
        }
        if (exp == 1) {
            return base;
        }

        long double half = hpow_recursive_impl(base * base, exp / 2);
        return (exp % 2 == 0) ? half : base * half;
    }

    template <typename BaseType, typename ExpType>
    long double hpow_recursive(BaseType base, ExpType exponent) {
        if constexpr (!std::is_arithmetic<BaseType>::value) {
            throw std::invalid_argument("hpow_recursive: BaseType must be numeric (int, double, float, etc.)");
        }

        if constexpr (!std::is_integral<ExpType>::value) {
            throw std::invalid_argument("hpow_recursive: ExpType must be an integer type");
        }

        if (base == 0 && exponent <= 0) {
            throw std::invalid_argument("hpow_recursive: Indeterminate form: 0^0 or division by zero.");
        }

        bool neg_exp = (exponent < 0);
        ExpType abs_exp = std::abs(exponent);
        long double base_ld = static_cast<long double>(base);
        long double result = hpow_recursive_impl(base_ld, abs_exp);

        return neg_exp ? 1.0 / result : result;
    }


}; // namespace hw