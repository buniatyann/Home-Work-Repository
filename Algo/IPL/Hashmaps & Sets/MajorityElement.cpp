#include <unordered_map>
#include <vector>

int majorityElement(const std::vector<int>& nums) {
    std::unordered_map<int, int> mp;
    for (int i : nums) {
        ++mp[i];
    }

    int ans = INT_MIN;
    for (const auto& [key, value] : mp) {
        if (value > nums.size() / 2) {
            ans = std::max(ans, key);
        }
    }

    return ans;
}

int majorityElement(const std::vector<int>& nums) {
    int count = 1;
    int majority = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] == majority) {
            ++count;
        }
        else {
            --count;
            if (count == 0) {
                count = 1;
                majority = nums[i];
            }
        }
    }

    return majority;
}