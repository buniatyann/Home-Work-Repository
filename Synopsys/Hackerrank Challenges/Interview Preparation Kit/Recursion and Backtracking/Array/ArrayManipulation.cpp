#include <bits/stdc++.h>

long arrayManipulation(int n, std::vector<std::vector<int>> queries) {
    // Initialize a temporary array of size n + 1 to handle range updates
    std::vector<long> tmp(n + 1, 0);

    // Apply the difference array concept for each query
    for (const auto& query : queries) {
        int first_i = query[0] - 1; // Convert to 0-based index
        int last_i = query[1] - 1;   // Convert to 0-based index
        long to_add = query[2];

        tmp[first_i] += to_add; // Start adding at the first index
        
        if (last_i + 1 < n) {   // Avoid out-of-bounds
            tmp[last_i + 1] -= to_add; // Stop adding after the last index
        }
    }

    // Find the maximum value using a prefix sum
    long max_value = 0;
    long current_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        current_sum += tmp[i]; // Build the actual values from the difference array
        if (current_sum > max_value) {
            max_value = current_sum; // Update maximum value found
        }
    }

    return max_value; // Return the maximum value in the array after all operations
}