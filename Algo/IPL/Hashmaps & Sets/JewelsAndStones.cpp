#include <string>
#include <unordered_set>

// Leetcode 771

int numJewelsInStones(const std::string& jewels, const std::string& stones) {
    std::unordered_set<char> st(jewels.begin(), jewels.end());
    int count = 0;
    for (char c : stones) {
        if (st.find(c) != st.end()) {
            ++count;
        }
    }

    return count;
}