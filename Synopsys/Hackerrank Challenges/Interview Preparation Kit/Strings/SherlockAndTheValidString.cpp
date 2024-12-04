#include <bits/stdc++.h>

/*
    Time O(n)
    Space O(k) (or O(1) for a fixed alphabet size)
*/
std::string isValid(std::string s) {
    // Dictionary to count occurrences of each character
    std::unordered_map<char, int> char_count;
    
    for (char charac : s) {
        char_count[charac]++;
    }
    
    // Dictionary to count the frequency of each character count
    std::unordered_map<int, int> frequency_count;
    for (auto& pair : char_count) {
        frequency_count[pair.second]++;
    }
    
    // There can be at most two distinct frequencies
    if (frequency_count.size() == 1) {
        return "YES";  // All characters have the same frequency
    }
    
    if (frequency_count.size() > 2) {
        return "NO";  // More than two different frequencies
    }
    
    // If there are exactly two frequencies, check the conditions
    std::vector<std::pair<int, int>> freq_list(frequency_count.begin(), frequency_count.end());
    int freq1 = freq_list[0].first;  // frequency
    int count1 = freq_list[0].second; // how many characters have this frequency
    int freq2 = freq_list[1].first;  // second frequency
    int count2 = freq_list[1].second; // how many characters have this frequency

    // Check if one of the frequencies can be reduced to form a valid string
    if ((count1 == 1 && (freq1 - 1 == freq2 || freq1 == 1)) || 
        (count2 == 1 && (freq2 - 1 == freq1 || freq2 == 1))) {
        return "YES";
    }
    
    return "NO";
}