#include <vector>
#include <algorithm>

/*
    Time O(n)
    Space O(n)
    veranayel
*/
// Helper function to get the value at a specified index from the 'values' vector.
// If the index is invalid (less than 0), return 0.
int get(const std::vector<int>& values, int index) {
    if (index < 0) {
        return 0;  // if index is out of bounds, return 0 (as no value exists before index 0)
    }
    
   return values[index];  // Otherwise, return the value at the given index    
}

// Function to compute the maximum subset sum such that no two elements are adjacent
int maxSubsetSum(const std::vector<int>& arr) {
    int n = arr.size();  // Get the size of the input array
    std::vector<int> maxUpTo(n);  // Vector to store the maximum subset sum up to each index
    
    // Loop through each element of the array
    for (int i = 0; i < n; i++) {
        int val = arr[i];  // The value of the current element
        int valOrZero = std::max(0, val);  // Ensure that if the current value is negative, treat it as 0
        
        // Get the maximum sum possible up to the previous index (i-1)
        int max1 = get(maxUpTo, i - 1);
        
        // Get the maximum sum possible up to two indices before (i-2)
        int max2 = get(maxUpTo, i - 2);
        
        // Update the current index with the maximum sum considering either:
        // - Taking the value of the current element along with the max sum up to two indices before (i-2)
        // - Skipping the current element and taking the max sum up to the previous index (i-1)
        maxUpTo[i] = std::max(max1, max2 + valOrZero);
    }
    
    return maxUpTo[n - 1];  // Return the maximum subset sum calculated for the last index
}