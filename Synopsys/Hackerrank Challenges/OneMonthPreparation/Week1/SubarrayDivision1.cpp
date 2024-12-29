#include <iostream>
#include <vector>

/*
    Time O(n)
    Space O(n)
*/
int birthday(std::vector<int> s, int d, int m) {
    // Initialize variables: summ to store the sum of the first 'm' elements,
    // and ways to count the number of valid subarrays whose sum is equal to 'd'.
    int summ = 0;
    int ways = 0;
    
    // Calculate the sum of the first 'm' elements in the array.
    for(int i = 0; i < m; ++i){
        summ += s[i];
    }
    
    // Check if the sum of the first 'm' elements is equal to 'd'.
    if(summ == d){
        ++ways;  // If it matches, increment the count of valid ways.
    }
    
    // Use a sliding window to check all other subarrays of length 'm'.
    // Start from the 'm'th element and slide the window to the right.
    for(int i = m; i < s.size(); ++i){
        // Update the sum by removing the element at the left of the window (i - m),
        // and adding the element at the current position (i).
        summ -= s[i - m];
        summ += s[i];
        
        // Check if the updated sum is equal to 'd'.
        if(summ == d){
            ++ways;  // If it matches, increment the count of valid ways.
        }
    }
    
    // Return the total number of valid subarrays found.
    return ways;
}
