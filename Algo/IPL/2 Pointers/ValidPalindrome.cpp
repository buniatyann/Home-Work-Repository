#include <string>

// Leetcode 125

bool isPalindrome(const std::string& s) {
    int l = 0;
    int r = s.length() - 1;
    
    while (l < r) {
        while (l < r && !std::isalnum(s[l])) {
            ++l;
        }
        while (l < r && !std::isalnum(s[r])) {
            --r;
        }

        if (std::tolower(s[l]) != std::tolower(s[r])) {
            return false;
        }
        
        ++l;
        --r;
    }
    
    return true;
}