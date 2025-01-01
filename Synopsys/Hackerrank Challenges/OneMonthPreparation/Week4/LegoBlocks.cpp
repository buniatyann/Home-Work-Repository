#include <vector>
#include <numeric>

/*
    Time O(m * n) + O(m ^ 2)
    Space O(m)
    veranayel
*/
long long legoBlocks(int n, int m) {
    const long long MOD = 1e9 + 7;  // Modulo value to prevent overflow

    // The number of combinations to build a single row for widths 0, 1, 2, 3
    std::vector<long long> row_combinations = {1, 1, 2, 4};
    
    // Build row combinations up to current wall's width
    while (row_combinations.size() <= m) { 
        // Sum the last 4 combinations (because a row can be built using up to 4 block sizes)
        long long new_combination = std::accumulate(row_combinations.end() - 4, row_combinations.end(), 0LL) % MOD;
        row_combinations.push_back(new_combination);  // Add the new combination
    }
    
    // Compute total combinations for constructing a wall of height N of varying widths
    std::vector<long long> total(m + 1);  // Stores the total combinations for width i
    for (int i = 0; i <= m; ++i) {
        total[i] = 1;
        // Raise the row combination to the power of n (since the wall has height N)
        for (int j = 0; j < n; ++j) {
            total[i] = (total[i] * row_combinations[i]) % MOD;
        }
    }
    
    // Find the number of unstable wall configurations
    // For a wall of height N with varying widths
    std::vector<long long> unstable = {0, 0};  // Unstable configurations for width 0 and 1
    
    // Divide the wall into a left and right part and calculate the number of ways
    // the left part and right part can violate the constraints
    for (int i = 2; i <= m; ++i) {
        long long result = 0;
        for (int j = 1; j < i; ++j) {
            // For each division, subtract unstable configurations from left part
            // and multiply with right part to find violations
            result = (result + (total[j] - unstable[j] + MOD) % MOD * total[i - j]) % MOD;
        }

        unstable.push_back(result);  // Store the result of the unstable part for this width
    }
    
    // The stable configurations are the total combinations minus the unstable ones
    return (total[m] - unstable[m] + MOD) % MOD;
}