#include <set>
#include <vector>
#include <algorithm>

/*
    Time O(n * log(n))
    Space O(n)
    veranayel
*/
long maximumSum(std::vector<long> a, long m) {
    int n = a.size();  // Get the size of the input vector 'a'
    std::vector<long> arr(n);  // This will store the prefix sums modulo 'm'
    std::set<long> f;  // A set to store the previously encountered prefix sums modulo m
    long ans = 0;  // This will store the maximum subarray sum modulo m

    // Compute the prefix sums modulo m
    arr[0] = a[0] % m;  // First element modulo m
    
    for (int i = 1; i < n; ++i) {
        // Compute the prefix sum modulo m
        arr[i] = (arr[i - 1] + a[i]) % m;
    }

    // Initialize the set with 0 (since the subarray sum from the start can be valid)
    f.insert(0);

    // Iterate through the prefix sum array and compute the maximum subarray sum modulo m
    for (int i = 0; i < n; ++i) {
        // Check for the maximum sum using the prefix sum at index 'i' and the smallest value seen so far
        auto it = f.begin();

        if (it != f.end()) {
            // Compute the difference and update 'ans' if it's larger
            ans = std::max(ans, arr[i] - *it);
        }

        // Find the smallest value greater than arr[i] using upper_bound
        it = f.upper_bound(arr[i]);

        if (it != f.end()) {
            // Compute the modulo difference and update 'ans' if it's larger
            ans = std::max(ans, (arr[i] - *it + m) % m);
        }

        // Insert the current prefix sum into the set to track it for future comparisons
        f.insert(arr[i]);
    }

    // Return the maximum sum modulo m found
    return ans;
}