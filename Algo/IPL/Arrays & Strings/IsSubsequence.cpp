#include <string>

// Leetcode 392
bool isSubsequence(const std::string& s, const std::string& t) {
    if (s.empty()) {
        return true;
    }

    int l = 0;
    for (std::size_t i = 0; i < t.length(); ++i) {
        if (t[i] == s[l]) {
            ++l;
            if (l == s.length()) {
                return true;
            }
        }
    }

    return false;
}