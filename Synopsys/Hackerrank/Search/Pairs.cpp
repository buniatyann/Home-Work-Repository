#include <bits/stdc++.h>

// Time O(n) Space O(n)
int pairs(int k, std::vector<int>& arr) {
    // Create a set to store unique elements from the array for fast lookups
    std::set<int> st(arr.begin(), arr.end());
    int pairs = 0; // Initialize a counter for the number of valid pairs

    // Iterate through the original array
    for (int i = 0; i < arr.size(); ++i) {
        // Check if there exists an element that forms a valid pair with arr[i]
        if (st.find(arr[i] + k) != st.end()) {
            ++pairs; // Increment the pair count if a valid pair is found
        }
    }
    
    return pairs; // Return the total count of valid pairs
}

// Time O(n) Space O(n)
int pairs(int k, std::vector<int>& arr) {
    // Use an unordered set for fast lookups
    std::unordered_set<int> st(arr.begin(), arr.end());
    int pairs = 0; // Initialize a counter for the number of valid pairs

    // Iterate through the unique elements in the set
    for (const int& num : st) {
        // Check if the complement (num + k) exists in the set
        if (st.count(num + k)) {
            ++pairs; // Increment the pair count if a valid pair is found
        }
    }
    
    return pairs; // Return the total count of valid pairs
}