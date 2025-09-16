#include <string>
#include <vector>

// Leetcode 228

std::vector<std::string> summaryRanges(std::vector<int>& nums) {
    std::vector<std::string> ans;
    for (int i = 0; i < nums.size(); ++i) {
        int min = nums[i];
        while (i < nums.size() - 1 && nums[i + 1] == nums[i] + 1) {
            ++i;
        }
        
        int max = nums[i];
        if (min == max) {
            ans.push_back(std::to_string(min));
        }
        else {
            ans.push_back(std::to_string(min) + "->" + std::to_string(max));
        }
    }

    return ans;
}