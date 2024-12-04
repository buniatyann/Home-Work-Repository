#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

/*
    Time O(n*log(n))
    Space O(log(n))
*/
int findMinDifference(std::vector<int>& arr) {
    // If there are fewer than 2 elements, return 0 as no pair exists
    if (arr.size() < 2) return 0;

    // Sort the array (
    std::sort(arr.begin(), arr.end());

    // Initialize the minimum difference to a large value
    int minn = INT_MAX;

    // Iterate over the sorted array and find the minimum difference
    for (size_t i = 1; i < arr.size(); ++i) {
        // Compute the absolute difference
        int diff = arr[i] - arr[i - 1];
        
        // If we find a difference of 0, return immediately since it's the smallest possible
        if (diff == 0) return 0;

        // Update the minimum difference
        minn = std::min(minn, diff);
    }

    return minn;
}


