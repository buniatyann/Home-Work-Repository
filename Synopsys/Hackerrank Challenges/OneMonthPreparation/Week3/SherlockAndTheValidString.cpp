#include <unordered_map>
#include <string>
#include <iostream>

/*
    Time O(n)
    Space O(n)
*/
std::string isValid(std::string s) {
    std::unordered_map<char, int> freq_map;
    // Count frequency of each character
    for (char c : s) {
        ++freq_map[c];
    }

    // Count how many characters have each frequency
    std::unordered_map<int, int> freq_count_map;
    for (auto& entry : freq_map) {
        ++freq_count_map[entry.second];
    }

    // Check the validity conditions
    if (freq_count_map.size() > 2) {
        return "NO"; // More than two different frequencies means not valid
    }

    if (freq_count_map.size() == 1) {
        return "YES"; // Only one frequency, all characters have the same frequency
    }

    // If we have exactly two frequencies, let's check the conditions
    auto it = freq_count_map.begin();
    int first_freq = it->first;
    int first_count = it->second;
    ++it;
    int second_freq = it->first;
    int second_count = it->second;

    // One frequency is 1 and it occurs once (one character can be removed)
    if ((first_freq == 1 && first_count == 1) || (second_freq == 1 && second_count == 1)) {
        return "YES";
    }

    // Frequencies differ by 1, and the higher frequency occurs exactly once
    if (std::abs(first_freq - second_freq) == 1 && (first_count == 1 || second_count == 1)) {
        return "YES";
    }

    return "NO"; // Otherwise, it's not valid
}