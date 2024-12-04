#include <iostream>      
#include <vector>        
#include <unordered_map> 
#include <string>        
#include <algorithm>     

// Helper function to get the frequency of characters in a string
std::unordered_map<char, int> frequency(const std::string& s) {
    std::unordered_map<char, int> res;
    // Count the frequency of each character in the string
    for (char ch : s) {
        res[ch]++;
    }
    return res;
}

/*
    Time O(n)
    Space O(n)
    veranayel
*/
// Function to perform the reverse shuffle merge and return the lexicographically smallest result
std::string reverseShuffleMerge(const std::string& s) {
    // Compute the frequency of each character in the input string
    std::unordered_map<char, int> char_freq = frequency(s);
    
    // Set up maps for characters already used in result and remaining characters
    std::unordered_map<char, int> used_chars;       // Tracks characters used in the final result
    std::unordered_map<char, int> remain_chars = char_freq; // Tracks remaining characters to be used

    // Result container (vector) to hold the lexicographically smallest sequence
    std::vector<char> res;

    // Helper lambda function to determine if a character can still be used
    auto can_use = [&](char ch) {
        // Can use the character if we still need more of it (half its count)
        return (char_freq[ch] / 2 - used_chars[ch]) > 0;
    };

    // Helper lambda function to determine if a character can be popped from the result
    auto can_pop = [&](char ch) {
        int needed_chars = char_freq[ch] / 2;
        // We can pop the character if we have more of it remaining than needed
        return (used_chars[ch] + remain_chars[ch] - 1 >= needed_chars);
    };

    // Traverse the string in reverse order
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        char ch = *it;

        // If we can still use this character, try adding it to the result
        if (can_use(ch)) {
            // While the result is not empty, and we can pop the last character for a better result
            while (!res.empty() && res.back() > ch && can_pop(res.back())) {
                char removed_char = res.back();  // Character to be removed
                res.pop_back();  // Pop the last character from the result (acting like a stack)
                used_chars[removed_char]--;  // Decrease its usage count
            }

            // Add the current character to the result
            used_chars[ch]++;  // Mark that this character is now used
            res.push_back(ch); // Push it to the result (vector)
        }

        // Decrease the count of remaining characters for this character
        remain_chars[ch]--;
    }

    // Convert the result vector into a string and return
    return std::string(res.begin(), res.end());
}
