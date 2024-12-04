#include<iostream>

/*
    Time O(log(n))
    Space O(1)
*/
long sumXor(long n) {
    // Count the number of zero bits in n
    long count_zeros = 0;  // Variable to store the count of zero bits

    // Iterate through the bits of n
    while (n > 0) {
        // Check if the current bit is 0
        if ((n & 1) == 0) {
            count_zeros++;  // Increment count_zeros if the current bit is 0
        }
        n >>= 1;  // Right shift n by 1 bit, effectively moving to the next bit
    }

    // The answer is 2 raised to the power of count_zeros
    // The number of valid `i` values is determined by the number of 0 bits in n.
    // Each 0 bit in n allows 2 choices (0 or 1) for the corresponding bit in i.
    // So, we calculate 2^count_zeros using the left shift operator (1L << count_zeros).
    return 1L << count_zeros;
}