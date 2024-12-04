#include <bits/stdc++.h>


// Time O(N ^ 2) Space O(N)
// Veranayel
int sherlockAndAnagrams(std::string s) {
    std::unordered_map<std::string, int> signature_count;

    // Generate all possible substrings and their signatures
    int n = s.size();
    
    for (int start = 0; start < n; ++start) {
        std::vector<int> char_count(26, 0); // Since we only have lowercase a-z
        
        for (int end = start; end < n; ++end) {
            char_count[s[end] - 'a']++; // Increment the count of the current character
            
            // Create a signature from the current character count
            std::string signature;

            for (int count : char_count) {
                signature += std::to_string(count) + '#'; // Use a delimiter to separate counts
            }
            
            signature_count[signature]++;
        }
    }

    // Count pairs of anagrammatic substrings
    int anagram_pairs = 0;
    
    for (const auto& entry : signature_count) {
        int count = entry.second;

        if (count > 1) {
            anagram_pairs += (count * (count - 1)) / 2; // nC2 = n * (n - 1) / 2
        }
    }

    return anagram_pairs;
}