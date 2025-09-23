#include <queue>
#include <vector>
#include <unordered_map>

// leetcode 347
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mp;
    std::priority_queue<std::pair<int, int>> q;
    for (int i : nums) {
        ++mp[i];
    }
    for (const auto& [key, value] : mp) {
        q.push(std::make_pair(value, key));
    }

    std::vector<int> ans;
    for (int i = 0; i < k; ++i) {
        ans.push_back(q.top().second);
        q.pop();
    }

    return ans;
}