#include <string>
#include <vector>

// Leetcode 14

std::string longestCommonPrefix(std::vector<std::string>& strs) {
    int j = 0;
    std::string ans = "";
    int min_len = INT_MAX;
    for (const std::string& st : strs) {
        min_len = std::min(min_len, static_cast<int>(st.length()));
    }

    for (int i = 0; i < min_len; ++i) {
        bool all = true;
        char c = strs[0][j]; 
        for (int k = 0; k < strs.size(); ++k) {
            if (strs[k][j] != c) {
                all = false;
                break;
            }
        }

        if (all) {
            ans += c;
            ++j;
        }
        else {
            break;
        }
    }

    return ans;
}