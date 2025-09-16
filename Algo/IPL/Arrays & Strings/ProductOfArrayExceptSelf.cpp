#include <vector>

// Leetcode 238 
// needs to be reviewed

std::vector<int> productExceptSelf(std::vector<int>& nums) {
    int zeros = 0;
    long long prod = 1;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 0) {
            ++zeros;
        }
        else {
            prod *= nums[i];
        }
    }

    
    std::vector<int> ans(nums.size(), 0);
    if (zeros > 1) {
        return ans;
    }
    else if (zeros == 1) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                ans[i] = static_cast<int>(prod);
            }
        }
    }
    else {
        for (int i = 0; i < nums.size(); ++i) {
            ans[i] = static_cast<int>(prod / nums[i]);
        }
    }

    return ans;
}