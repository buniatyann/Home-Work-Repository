#include <vector>
#include <algorithm>

/*
    Time O(n + q) where q is the number of querries
    Space O(n)
*/
long arrayManipulation(int n, std::vector<std::vector<int>> queries) {
    // Create an array to store the difference of values.
    std::vector<long> s(n + 1, 0);  // Initialize with zeros
    
    // Process each query
    for (auto &query : queries) {
        int start = query[0] - 1;  // Convert to 0-based index
        int end = query[1];        // End is exclusive, so no change needed
        long value = query[2];
        
        // Apply the difference array technique
        s[start] += value;
        if (end < n) {
            s[end] -= value;
        }
    }

    // Now calculate the maximum value using prefix sum
    long maxx = 0;
    long current = 0;

    for (int i = 0; i < n; ++i) {
        current += s[i];  // Accumulate the changes
        maxx = std::max(maxx, current);  // Track the maximum value
    }

    return maxx;
}
