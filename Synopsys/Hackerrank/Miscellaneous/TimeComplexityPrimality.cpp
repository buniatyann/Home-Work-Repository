#include <cmath>
#include <string>

/*
    Time O(sqrt(n))
    Space O(1)
*/
std::string primality(int n) {
    // Numbers less than or equal to 1 are not prime
    if (n == 1) {
        return "Not prime";  // 1 is not prime
    }

    // 2 and 3 are prime numbers
    if (n == 2 || n == 3) {
        return "Prime";  // 2 and 3 are prime
    }

    // Eliminate even numbers greater than 2 (all even numbers are not prime)
    if (n % 2 == 0) {
        return "Not prime";  // Even numbers greater than 2 are not prime
    }

    // Check for divisibility from 2 up to sqrt(n)
    // We only need to check for factors from 2 to sqrt(n), since if a number is divisible by any number larger than its square root, 
    // the corresponding factor will have already been found as a smaller factor.
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            return "Not prime";  // If n is divisible by i, it's not a prime number
        }
    }

    // If no factors were found, the number is prime
    return "Prime";  // n is prime
}

/*
    Time O(sqrt(n))
    Space O(1)
*/
std::string primality(int n) {
    // Numbers less than or equal to 1 are not prime
    if (n <= 1) {
        return "Not prime";  // 1 and negative numbers are not prime
    }

    // 2 and 3 are prime numbers
    if (n == 2 || n == 3) {
        return "Prime";  // 2 and 3 are prime numbers
    }

    // Eliminate multiples of 2 and 3 early (all even numbers and multiples of 3 are not prime)
    if (n % 2 == 0 || n % 3 == 0) {
        return "Not prime";  // All even numbers greater than 2 and multiples of 3 are not prime
    }

    // Check for divisibility from 5 to sqrt(n) using a 6-step approach
    // This is based on the observation that all primes greater than 3 are of the form 6k ± 1.
    // So, we check for divisibility by i and i + 2 where i starts from 5 and increments by 6.
    for (int i = 5; i * i <= n; i += 6) {
        // Check if n is divisible by i or i + 2 (i.e., 5, 7, 11, 13, 17, 19, etc.)
        if (n % i == 0 || n % (i + 2) == 0) {
            return "Not prime";  // If n is divisible by i or i + 2, it's not prime
        }
    }

    // If no divisors are found, the number is prime
    return "Prime";  // n is prime if no divisors were found
}
