#include <vector>

/*
    Time O(1)
    Space O(1)
*/
// Function to convert the number to its inverted binary representation
std::vector<bool> long_to_inv_bin(long n) {
    int i = 31;
    std::vector<bool> ans(32);
    
    // Convert the number to binary and invert the bits
    while(n) {
        ans[i] = !(n % 2);  // Invert the bit (0 becomes 1, 1 becomes 0)
        n /= 2;
        --i;
    }
    
    // Fill remaining higher bits with 1 (if the number is smaller than 32 bits)
    while(i >= 0) {
        ans[i] = 1;  // Set remaining bits to 1
        --i;
    }
    
    return ans;
}

// Function to flip the bits of a given number
long flippingBits(long n) {
    // Get the inverted binary representation of n
    std::vector<bool> vec = long_to_inv_bin(n);
    long ans = 0;
    long two = 1;

    // Construct the integer from the binary vector by iterating over it
    for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
        ans += (*i) * two;  // Accumulate the value by adding the corresponding bit
        two *= 2;  // Multiply by 2 to handle the next bit position
    }

    return ans;  // Return the resulting number
}



