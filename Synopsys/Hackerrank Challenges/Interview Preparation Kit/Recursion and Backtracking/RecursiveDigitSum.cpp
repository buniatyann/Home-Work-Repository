#include <iostream>
#include <string>

/*
    Time O(d + log(summ))
    Space O(log(summ))
    where d is the number of digits in n and summ is the result of multiplying the sum of digits of n by k.
*/
int superDigit(std::string n, int k) {
    // Calculate the sum of digits of `n`
    long summ = 0;
    // Loop through each character in the string `n`
    for (char c : n) {
        // Convert the character `c` to its integer value by subtracting '0' (ASCII conversion)
        summ += (c - '0');
    }
    
    // Multiply the sum by `k` since `n` is repeated `k` times
    summ *= k;

    // Recursively reduce the number by summing its digits until a single digit
    // Base case: If `summ` is a single digit, return it
    if (summ < 10) {
        return summ;
    }
    
    // Recursively call superDigit with the sum of digits of the current `summ`
    // Convert `summ` to string for the next recursive step
    return superDigit(std::to_string(summ), 1);
}
