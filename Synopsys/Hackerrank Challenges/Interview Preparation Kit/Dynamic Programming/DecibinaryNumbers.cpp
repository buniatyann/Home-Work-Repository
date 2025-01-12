#include <bits/stdc++.h> // Include all standard headers

// Declare the necessary global arrays for precomputation.
std::vector<std::vector<long>> cache(300000, std::vector<long>(19)), two(10, std::vector<long>(19)), ten(10, std::vector<long>(19));
std::vector<long> decimalValue; // Array to store cumulative sums of decibinary numbers.

// Function to precompute all the necessary information for quick lookup during queries.
void global_information() {
    // Precompute two and ten arrays for efficiency.
    for (int K = 0; K <= 18; ++K) { // Loop through the range of digit positions (0 to 18).
        for (int d = 0; d <= 9; ++d) { // Loop through the digits (0 to 9).
            two[d][K] = d * std::pow(2, K);  // Store d * 2^K in 'two' array.
            ten[d][K] = d * std::pow(10, K); // Store d * 10^K in 'ten' array.
        }
    }

    // Initialize the base cases for the cache array (number of valid decibinary numbers with given digit length).
    for (int K = 0; K <= 18; ++K) {
        cache[0][K] = 1; // There is only one decibinary number with length K when n = 0 (i.e., the number 0).
    }

    // Cache initialization for the first 10 numbers and their digit counts.
    for (int n = 0; n <= 9; ++n) {
        cache[n][0] = 1; // Each of the digits 0 to 9 is itself a valid decibinary number with length 0.
    }

    // Fill the cache array for all n up to the size of the cache.
    for (int n = 1; n < cache.size(); ++n) {
        for (int K = 1; K <= 18; ++K) { // Loop through possible digit positions.
            for (int d = 0; d <= 9 && n - two[d][K] >= 0; ++d) { // Loop through possible digits (0 to 9).
                cache[n][K] = cache[n][K] + cache[n - two[d][K]][K - 1]; // Accumulate values based on previous results.
            }
        }
    }

    // Precompute the decimalValue array with cumulative sums of decibinary counts.
    decimalValue.push_back(1); // Base case: the first value is 1 (the 0th decibinary number).
    for (int n = 1; n < cache.size(); ++n) {
        decimalValue.push_back(decimalValue.back() + cache[n][18]); // Accumulate decibinary counts.
    }
}

/*
    Time O(K) 
    Space O(1)
*/
long decibinaryNumbers(long x) {
    if (x == 1) return 0; // The first decibinary number is 0 by definition.
    
    long answer = 0; // The variable to store the resulting decibinary number.
    
    // Find the interval in which the x-th number lies.
    int v = std::distance(decimalValue.begin(), std::lower_bound(decimalValue.begin(), decimalValue.end(), x));
    long position = x - decimalValue[v - 1]; // Calculate the position within the interval.
   
    // Backtrack and determine the digits of the decibinary number.
    while (v > 0) {
        // Find the smallest K such that the position can be formed using the current value of v.
        int K = std::distance(cache[v].begin(), std::lower_bound(cache[v].begin(), cache[v].end(), position)), d = 0;
        
        if (K == 0) {
            answer = answer + v; // If K == 0, we add v directly to the answer and break.
            break;
        }
        
        long temp = 0; // Temporary variable to hold cumulative counts during digit selection.
        
        // Try each digit from 0 to 9 and find the one that corresponds to the current position.
        for (int digit = 0; digit <= 9 && v - two[digit][K] >= 0; ++digit) {
            temp = temp + cache[v - two[digit][K]][K - 1]; // Update temp with decibinary counts for previous digits.
        
            if (position <= temp) { // If the current position is within the temp range, select the digit.
                d = digit;
                break;
            }
        }
        
        answer = answer + ten[d][K]; // Add the corresponding power of 10 value for the selected digit.
        position = position - temp + cache[v - two[d][K]][K - 1]; // Update the position for the next iteration.
        v = v - two[d][K]; // Decrease v to reflect the choice of the digit.
    }
    
    return answer; // Return the computed decibinary number.
}

int main() {
    global_information();  // Precompute necessary information.

    int q;
    long x;
    std::cin >> q;  // Read the number of queries.

    for (int i = 1; i <= q; ++i) {
        std::cin >> x;  // Read each query value.
        std::cout << decibinaryNumbers(x) << '\n';  // Compute and output the result for each query.
    }

    return 0;
}
