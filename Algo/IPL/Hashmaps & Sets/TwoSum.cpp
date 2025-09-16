#include <unordered_map>
#include <vector>

// Leetcode 1

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); ++i) {
        if (mp.find(target - nums[i]) != mp.end()) {
            return {mp[target - nums[i]], i};
        }
        else {
            mp.insert({nums[i], i});
        }
    }

    return {};
}