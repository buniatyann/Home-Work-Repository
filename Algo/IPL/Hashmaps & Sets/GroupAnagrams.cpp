#include <vector>
#include <unordered_map>
#include <string>

// Leetcode 49

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> mp;
    for (const auto& c : strs) {
        mp[get_frequency(c)].push_back(c);
    }

    std::vector<std::vector<std::string>> ans; 
    for (const auto& [key, value] : mp) {
        ans.push_back(value);
    }

    return ans;
}

std::string get_frequency(const std::string& str) {
    std::vector<int> vec(26, 0);
    for (char i : str) {
        ++vec[i - 'a'];
    }

    std::string ans = "";
    for (int i : vec) {
        ans += std::to_string(i);
        ans += '#';
    }

    return ans;
}   