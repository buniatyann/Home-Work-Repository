#include <unordered_map>
#include <string>

// leetcode 242
bool isAnagram(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    
    std::unordered_map<char, int> mp1;
    for (char c : s) {
        ++mp1[c];
    }
    
    std::unordered_map<char, int> mp2;
    for (char c : t) {
        ++mp2[c];
    }

    return mp1 == mp2;
}