#include <vector>
#include <algorithm>

// Leetcode 56 

std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) {
        return {{}};
    }
    std::vector<std::vector<int>> ans;
    std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, 
              const std::vector<int>& b) 
    {
        return a[0] < b[0];
    });

    ans.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= ans.back()[1]) {
            ans.back()[1] = std::max(ans.back()[1], intervals[i][1]);
        }
        else {
            ans.push_back(intervals[i]);
        }
    }

    return ans;
}