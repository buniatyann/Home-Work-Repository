#include <bits/stdc++.h>

// Time O(n) Space O(1) 
int alternatingCharacters(std::string& s) {
    int count = 0; // Count of deletions needed

    // Iterate through the string starting from the second character
    for (size_t i = 1; i < s.length(); ++i) {
        // If the current character is the same as the previous one
        if (s[i] == s[i - 1]) {
            count++; // Increment the count of deletions needed
        }
    }

    return count; // Return the total deletions needed
}

// Time O(n) Space O(1) 
int alternatingCharacters(std::string& s) {
    int count = 0; // Count of deletions needed

    // Iterate through the string starting from the second character
    for (size_t i = 1; i < s.length(); ++i) {
        count += s[i] ==s[i - 1];
    }

    return count; // Return the total deletions needed
}