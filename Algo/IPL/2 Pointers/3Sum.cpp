#include <vector>
#include <algorithm>

// Leetcode 15

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> ans;
    
    for (int i = 0; i < nums.size() - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        
        int l = i + 1;
        int r = nums.size() - 1;
        int target = -nums[i];
        
        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum == target) {
                ans.push_back({nums[i], nums[l], nums[r]});
                while (l < r && nums[l] == nums[l + 1]) ++l;
                while (l < r && nums[r] == nums[r - 1]) --r;
                ++l;
                --r;
            }
            else if (sum > target) {
                --r;
            }
            else {
                ++l;
            }
        }
    }
    
    return ans;
}


/*
    Logic -> slide -> object --> shape --> geoshape
                                       --> font
                                       --> color
                                       --> other objects
                                       --> functionality for them
                             --> handling functionality
                             --> parsing process --> lexer
                                                 --> parser
                                                 --> tokenizer

                             -->   
*/