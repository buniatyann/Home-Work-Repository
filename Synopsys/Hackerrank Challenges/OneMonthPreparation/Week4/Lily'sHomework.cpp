#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>  // For std::greater

// Helper function to count the number of swaps required to transform the array into sorted_arr
int count_swaps(std::vector<int>& arr, std::vector<int>& sorted_arr, std::unordered_map<int, int>& original_indices) {
    int swaps = 0;  // Counter for the number of swaps
    std::vector<int> copy_arr = arr;  // Create a copy of the original array to perform swaps on

    // Iterate through the array and compare each element to the corresponding element in sorted_arr
    for (int i = 0; i < arr.size(); i++) {
        // If the current element is not in the correct position, swap it
        if (copy_arr[i] != sorted_arr[i]) {
            // Find the index of the element in the sorted array
            int target_index = original_indices[sorted_arr[i]];
            
            // Swap elements to their correct positions
            std::swap(copy_arr[i], copy_arr[target_index]);

            // Update the original indices map with the new positions
            original_indices[copy_arr[i]] = i;
            original_indices[copy_arr[target_index]] = target_index;

            swaps++;  // Increment swap count
        }
    }

    return swaps;  // Return the total number of swaps required
}

/*
    Time O(n * log(n))
    Space O(n)
*/
int lilysHomework(std::vector<int> arr) {
    int n = arr.size();  // Get the size of the array

    // Create two copies of the original list for ascending and descending order sorting
    std::vector<int> ascending_arr = arr;  // Copy for sorting in ascending order
    std::vector<int> descending_arr = arr;  // Copy for sorting in descending order

    // Create two maps to keep track of the original indices of the elements for each sorted version
    std::unordered_map<int, int> original_indices_ascending;
    std::unordered_map<int, int> original_indices_descending;

    // Initialize the original index maps for both sorted arrays
    for (int i = 0; i < n; i++) {
        original_indices_ascending[ascending_arr[i]] = i;
        original_indices_descending[descending_arr[i]] = i;
    }

    // Sort the arrays in ascending and descending order
    std::sort(ascending_arr.begin(), ascending_arr.end());  // Sort in ascending order
    std::sort(descending_arr.begin(), descending_arr.end(), std::greater<int>());  // Sort in descending order

    // Count the number of swaps required to sort the array in ascending order
    int sorted_swaps = count_swaps(arr, ascending_arr, original_indices_ascending);

    // Count the number of swaps required to sort the array in descending order
    int sorted_reverse_swaps = count_swaps(arr, descending_arr, original_indices_descending);

    // Return the minimum of the two swap counts
    return std::min(sorted_swaps, sorted_reverse_swaps);
}
