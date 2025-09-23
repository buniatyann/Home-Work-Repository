#include <queue>
#include <vector>

// leetcode 215
int findKthLargest(std::vector<int>& nums, int k) {
    std::priority_queue<int> q(nums.begin(), nums.end());
    for (int i = 0; i < k - 1; ++i) {
        q.pop();
    }

    return q.top();
}