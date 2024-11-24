#include <vector>

/*
    Time O(1)
    Space O(1)
*/
std::vector<bool> long_to_inv_bin(long n) {
    int i = 31;  // Start from the most significant bit (31st bit for 32-bit integer)
    std::vector<bool> ans(32);  // Vector to store the binary representation

    // Convert the number to binary and invert the bits
    while (n) {
        ans[i] = !(n & 1);  // Invert the bit (0 becomes 1, 1 becomes 0)
        n >>= 1;             // Right shift the number by 1 (move to the next bit)
        --i;                 // Move to the next position in the binary vector
    }

    // Fill remaining higher bits with 1 (if the number is smaller than 32 bits)
    while (i >= 0) {
        ans[i] = 1;  // Set remaining bits to 1
        --i;         // Move to the next position in the binary vector
    }

    return ans;
}

// Function to flip the bits of a given number
long flippingBits(long n) {
    // Get the inverted binary representation of n
    std::vector<bool> vec = long_to_inv_bin(n);
    long ans = 0;
    long two = 1;

    // Reconstruct the integer from the binary vector by iterating over it
    // Starting from the least significant bit (the reverse of original binary order)
    for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
        ans += (*i) * two;  // Add the corresponding bit multiplied by the place value (2^i)
        two <<= 1;           // Multiply by 2 to handle the next bit position (2^i)
    }

    return ans;  // Return the resulting number
}



