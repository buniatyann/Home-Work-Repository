#include <bits/stdc++.h>

int hourglassSum(std::vector<std::vector<int>> arr) {
    // Initialize the maximum sum to a very low value (less than the minimum possible hourglass sum).
    int sum = -1000; 

    // Loop through the 2D array to find the top-left corner of each hourglass.
    for (int i = 0; i < 4; i++) {          // i goes from 0 to 3 to cover rows 0-3 (hourglass top)
        for (int x = 0; x < 4; x++) {      // x goes from 0 to 3 to cover columns 0-3 (hourglass left)
            // Calculate the sum of the top part of the hourglass
            int top = arr[i][x] + arr[i][x + 1] + arr[i][x + 2]; 
            // Calculate the middle part of the hourglass
            int middle = arr[i + 1][x + 1]; 
            // Calculate the sum of the bottom part of the hourglass
            int bottom = arr[i + 2][x] + arr[i + 2][x + 1] + arr[i + 2][x + 2]; 
            
            // Check if the current hourglass sum is greater than the previously recorded maximum sum
            if (top + middle + bottom > sum) {
                sum = top + middle + bottom; // Update the maximum sum if the current is greater
            }
        }
    }
    
    // Return the maximum hourglass sum found
    return sum; 
}