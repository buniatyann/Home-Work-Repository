#include <vector>
#include <cstddef>
#include <functional>
#include <limits>
#include <queue>

std::pair<int, int> operator+(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

long shortestPath(int start_i, int start_j, 
                  const std::vector<std::vector<bool>>& grid,
                  int dest_i, int dest_j)
{
    if (grid.empty() || grid[0].empty()) {
        return -1L;
    }

    int n = grid.size();
    int m = grid[0].size();
    if (start_i >= n || start_j >= m || dest_i >= n || dest_j >= m ||
        start_i < 0 || start_j < 0 || dest_i < 0 || dest_j < 0 ||
        grid[start_i][start_j] || grid[dest_i][dest_j]) {
        return -1L;
    }

    if (start_i == dest_i && start_j == dest_j) {
        return 0L;
    }

    std::function<bool(int, int)> in_bounds = [n, m](int i, int j) {
        return i >= 0 && j >= 0 && i < n && j < m;
    };

    std::vector<std::vector<long>> arr(n, std::vector<long>(m, std::numeric_limits<long>::max()));
    std::vector<std::pair<int, int>> directions = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };

    using Pos = std::pair<int, int>;
    std::queue<Pos> q;
    arr[start_i][start_j] = 0;
    q.push({start_i, start_j});
    while (!q.empty()) {
        Pos curr = q.front();
        q.pop();
        int ci = curr.first;
        int cj = curr.second;

        for (const auto& d : directions) {
            Pos next = curr + d;
            int ni = next.first;
            int nj = next.second;
            if (in_bounds(ni, nj) && !grid[ni][nj] && arr[ni][nj] == std::numeric_limits<long>::max()) {
                arr[ni][nj] = arr[ci][cj] + 1;
                if (ni == dest_i && nj == dest_j) {
                    return arr[dest_i][dest_j];
                }
                
                q.push(next);
            }
        }
    }

    return -1L;
}