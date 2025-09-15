#include <vector>
#include <cmath>

// Leetcode 2239
int findClosestNumber(std::vector<int>& nums) {
    int minn = nums[0];
    for (int i : nums) {
        if (std::abs(i) < std::abs(minn)) {
            minn = i;
        }
        else if (std::abs(i) == std::abs(minn) && i > minn) {
            minn = i;
        }
    }

    return minn;
}