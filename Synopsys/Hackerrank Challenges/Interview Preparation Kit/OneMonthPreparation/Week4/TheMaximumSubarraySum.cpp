#include <vector>
#include <algorithm>

/*
    Time O(n * log(n))
    Space O(1) why?
*/
std::vector<int> maxSubarray(std::vector<int> arr) {
    // Step 1: Initialize max_sum and curr_sum with the first element of the array
    int max_sum = arr[0];
    int curr_sum = arr[0];
    
    // Step 2: Apply Kadane's Algorithm to find the maximum subarray sum
    // Iterate through the array starting from the second element
    for (int i = 1; i < arr.size(); ++i) {
        // Update curr_sum: either add the current element to the current subarray
        // or start a new subarray with the current element
        curr_sum = std::max(curr_sum + arr[i], arr[i]);
        
        // Update max_sum: keep track of the largest subarray sum found so far
        max_sum = std::max(max_sum, curr_sum);
    }

    // Step 3: Sort the array in descending order (largest to smallest)
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    
    // Step 4: Calculate the sum of the largest elements in the sorted array
    int sub_sum = arr[0]; // Start with the largest element in the sorted array

    // Step 5: Iterate through the rest of the sorted array
    // and accumulate the sum as long as adding the next element doesn't reduce the sum
    for (int i = 1; i < arr.size(); ++i) {
        // If adding arr[i] decreases the sub_sum, stop adding more elements
        if (sub_sum + arr[i] < sub_sum)
            break;
        else
            sub_sum += arr[i]; // Otherwise, add the element to sub_sum
    }

    // Step 6: Return the results as a vector containing both sums
    return {max_sum, sub_sum};
}
