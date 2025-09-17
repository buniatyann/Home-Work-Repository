#include <vector>

// Leetcode 11

int maxArea(const std::vector<int>& heights) {
    int l = 0;
    int r = heights.size() - 1;
    int maxx = 0;
    while (l < r) {
        int area = (r - l) * std::min(heights[l], heights[r]);
        maxx = std::max(maxx, area);
        if (heights[l] < heights[r]) {
            ++l;
        }
        else {
            --r;
        }
    }

    return maxx;
}