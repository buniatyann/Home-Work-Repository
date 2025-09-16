#include <vector>
#include <algorithm>

// Leetcode 48

void rotate(std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix.size(); ++j) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (auto& i : matrix) {
        std::reverse(i.begin(), i.end());
    }
}