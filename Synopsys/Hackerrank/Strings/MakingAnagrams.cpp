#include <bits/stdc++.h>

// Time O(N + M) Space O(1)
int makeAnagram(std::string a, std::string b) {
    // Create two vectors to count the frequency of each character (a-z) in both strings
    std::vector<int> s1(26, 0); // Frequency count for string 'a'
    std::vector<int> s2(26, 0); // Frequency count for string 'b'
    
    // Count the frequency of characters in the first string
    for (char i : a) {
        s1[i - 'a']++; // Increment the count for the character (assumes lowercase letters)
    }
    
    // Count the frequency of characters in the second string
    for (char i : b) {
        s2[i - 'a']++; // Increment the count for the character (assumes lowercase letters)
    }
    
    int count = 0; // Initialize a counter for the number of deletions needed
    
    // Calculate the total number of deletions needed to make both strings anagrams
    for (int i = 0; i < 26; ++i) {
        count += abs(s1[i] - s2[i]); // Add the difference in counts for each character
    }
    
    return count; // Return the total number of deletions needed
}

// Time O(N + M) Space O(k) -> Effectively O(1) for practical cases 
int makeAnagram(std::string a, std::string b) {
    std::unordered_map<char, int> charCount;

    for (char c : a) {
        charCount[c]++;
    }

    for (char c : b) {
        charCount[c]--;
    }

    int count = 0;

    for (const auto& pair : charCount) {
        count += abs(pair.second);
    }

    return count;
}
