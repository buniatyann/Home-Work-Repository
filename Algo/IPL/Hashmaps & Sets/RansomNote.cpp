#include <unordered_map>
#include <string>

// Leetcode 383

bool canConstruct(const std::string& ransomNote, const std::string& magazine) {
    std::unordered_map<char, int> mp;
    for (int i = 0; i < magazine.length(); ++i) {
        ++mp[magazine[i]];
    }

    for (int i = 0; i < ransomNote.length(); ++i) {
        if (mp.find(ransomNote[i]) == mp.end()) {
            return false;
        }
        else if (mp[ransomNote[i]] == 0) {
            return false;
        }
        else {
            --mp[ransomNote[i]];
        }
    }

    return true;
}