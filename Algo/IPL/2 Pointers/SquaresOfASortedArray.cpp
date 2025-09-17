#include <vector>
#include <algorithm>

// Leetcode 977

std::vector<int> sortedSquares(const std::vector<int>& nums) {
    std::vector<int> ans;
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        if (nums[r] * nums[r] >= nums[l] * nums[l]) {
            ans.push_back(nums[r] * nums[r]);
            --r;
        }
        else {
            ans.push_back(nums[l] * nums[l]);
            ++l;
        }
    }
    
    std::reverse(ans.begin(), ans.end());
    return ans;
}