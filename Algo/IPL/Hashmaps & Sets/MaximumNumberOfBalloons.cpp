#include <unordered_map>
#include <string>

// Leetcode 1189

int maxNumberOfBalloons(const std::string& text) {
    std::unordered_map<char, int> mp;
    for (char c : text) {
        ++mp[c];
    }

    std::string word = "balloon";
    int maxx = INT_MAX;
    for (char c : word) {
        if (c == 'l' || c == 'o') {
            if (mp[c] < 2) {
                return 0;
            }

            maxx = std::min(maxx, mp[c] / 2);
        }
        else {
            maxx = std::min(maxx, mp[c]);
        }
    }

    return maxx;
}