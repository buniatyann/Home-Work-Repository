#include <string>


// Leetcode 1768
std::string mergeAlternately(const std::string& word1, std::string& word2) {
    std::string ans;
    int l = 0;
    int r = 0;
    while  (l < word1.length() && r < word2.length()) {
        ans += word1[l];
        ans += word2[r];
        ++l;
        ++r;
    } 

    while (l < word1.length()) {
        ans += word1[l];
        ++l;
    }

    while (r < word2.length()) {
        ans += word2[r];
        ++r;
    }

    return ans;
}