#include<bits/stdc++.h>

long substrCount(int n, std::string s) {
    long count = 0; // To keep track of the number of special substrings

    // First, count groups of identical characters
    int similar = 1; // Start with the first character as a group of one
    
    for (int i = 1; i < n; ++i) {
        // If the current character is the same as the previous one
        if (s[i] == s[i - 1]) {
            similar++; // Increment the count for this group of identical characters
        } else {
            // Add the number of special substrings for the current group
            count += (similar * (similar + 1)) / 2; // Sum of the first `similar` natural numbers
            similar = 1; // Reset for the next character
        }
    }
    
    // Handle the last group of identical characters
    count += (similar * (similar + 1)) / 2;

    // Now check for special cases where there's a different character in the middle
    for (int i = 1; i < n - 1; ++i) {
        // Check if characters on both sides of the current character are the same and different from it
        if (s[i - 1] == s[i + 1] && s[i - 1] != s[i]) {
            char ch = s[i - 1]; // Store the character on either side of the middle
            int length = 1; // Initialize length for checking outward
            
            // Check for palindromic structure: expand outwards as long as the conditions hold
            while (i - length >= 0 && i + length < n 
                    && s[i - length] == s[i + length] 
                    && s[i - length] == ch 
                    && s[i + length] == ch) 
            {
                count++; // Count this special substring
                length++; // Increment length for the next check
            }
        }
    }

    return count; // Return the total count of special substrings
}
