#include <queue>
#include <vector>

// leetcode 1046
int lastStoneWeight(const std::vector<int>& stones) {
    if (stones.empty()) {
        return 0;
    }

    std::priority_queue<int> q(stones.begin(), stones.end());
    while (!q.empty() && q.size() != 1) {
        int first = q.top();
        q.pop();
        int second = q.top();
        q.pop();
        q.push(first - second);
    }

    return q.top();
}