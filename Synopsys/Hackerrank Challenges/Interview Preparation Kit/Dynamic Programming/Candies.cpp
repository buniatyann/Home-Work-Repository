#include <vector>
#include <algorithm>

/*
    Time O(n)
    Space O(n)
*/
long candies(int n, std::vector<int> arr) {
    // Initialize candies array with 1 candy for each child
    std::vector<int> candies(n, 1);

    // Traverse the array from left to right
    // Each child gets more candies if they have a higher rating than the previous child
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            candies[i] = candies[i - 1] + 1; // Increase candy count
        }
    }

    // Traverse the array from right to left
    // Adjust candy distribution to ensure that a child with a higher rating than the next one gets more candies if necessary
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            // Ensure the current child gets at least as many candies as needed for the local comparison
            candies[i] = std::max(candies[i], candies[i + 1] + 1);
        }
    }

    // Calculate and return the total number of candies by summing the values in the candies array
    long total_candies = 0;
    for (int i = 0; i < n; i++) {
        total_candies += candies[i];
    }
    
    return total_candies;
}