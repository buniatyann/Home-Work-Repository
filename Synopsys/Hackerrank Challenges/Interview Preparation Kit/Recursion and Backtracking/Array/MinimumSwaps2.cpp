#include <bits/stdc++.h>

int minimumSwaps(std::vector<int> arr) {
    // Get the size of the array
    int n = arr.size();
    // Initialize the count of minimum swaps to 0
    int minSwaps = 0;

    // Iterate through each element in the array
    for (int i = 0; i < n; i++) {
        // While the current element is not in its correct position
        while (arr[i] != i + 1) {
            // Swap the current element with the element at its correct position
            std::swap(arr[i], arr[arr[i] - 1]);
            // Increment the swap count each time a swap is made
            minSwaps++;
        }
    }
    
    // Return the total number of swaps needed to sort the array
    return minSwaps; 
}