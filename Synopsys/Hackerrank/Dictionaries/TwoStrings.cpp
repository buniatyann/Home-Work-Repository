#include <bits/stdc++.h>


// Time O(n + m) Space O(k) where k is the number of unique characters
std::string twoStrings(std::string s1, std::string s2) {
    std::unordered_map<char, bool> mp;

    // Count characters in s1
    for(char c: s1){
        mp[c] = true; // Just mark the character as existing
    }
    
    // Check if any character in s2 exists in s1
    for(char i : s2){
        if(mp.find(i) != mp.end()){ // Check if the character is found
            return "YES";
        }
    }
    
    return "NO";
}

// Time O(n + m) Space O(1)
std::string twoStrings(std::string s1, std::string s2) {
    bool chr[26] = { false };

    for(char c : s1){
        chr[c - 'a'] = true;
    }

    for(char c : s2){
        if(chr[c - 'a']){
            return "YES";
        }
    }

    return "NO";
}