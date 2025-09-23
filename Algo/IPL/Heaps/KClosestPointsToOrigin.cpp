#include <queue>
#include <vector>
#include <cmath>

// leetcode 973

std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, 
                                           int k)  {
    std::priority_queue<std::pair<double, int>> q;
    for (int i = 0; i < points.size(); ++i) {
        double distance = std::sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        q.push(std::make_pair(-distance, i));
    }

    std::vector<std::vector<int>> ans;
    for (int i = 0; i < k; ++i) {
        ans.push_back(points[q.top().second]);
        q.pop();
    }

    return ans;
}