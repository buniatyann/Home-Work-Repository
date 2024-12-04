#include <bits/stdc++.h>

/*
    Time: O(Q) -> Q is the number of queries 
    Space: O(N) -> N is the number of distinct elements
    Veranayel
*/ 
std::vector<int> freqQuery(std::vector<std::vector<int>> queries) {
    std::unordered_map<int, int> mp;     // Map to count occurrences of numbers
    std::unordered_map<int, int> freq_map; // Map to count how many numbers have a certain frequency
    std::vector<int> ans;

    for (const auto& query : queries) {
        int q = query[0];
        int n = query[1];

        if (q == 1) {
            // Increment the count of number n
            if (mp[n] > 0) {
                // If n already exists, decrement its frequency in freqMap
                freq_map[mp[n]]--;
                if (freq_map[mp[n]] == 0) {
                    freq_map.erase(mp[n]);
                }
            }
            mp[n]++;
            freq_map[mp[n]]++; // Increment frequency for new count of n
        } 
        else if (q == 2) {
            // Decrement the count of number n if it exists
            if (mp[n] > 0) {
                freq_map[mp[n]]--; // Decrement frequency in freqMap
                
                if (freq_map[mp[n]] == 0) {
                    freq_map.erase(mp[n]);
                }
                
                mp[n]--; // Decrement count of n
                
                if (mp[n] > 0) {
                    freq_map[mp[n]]++; // Update frequency if still > 0
                }
            }
        } 
        else if (q == 3) {
            // Check if any number has exactly frequency n
            if (freq_map.find(n) != freq_map.end()) {
                ans.push_back(1);
            } 
            else {
                ans.push_back(0);
            }
        }
    }

    return ans;
}