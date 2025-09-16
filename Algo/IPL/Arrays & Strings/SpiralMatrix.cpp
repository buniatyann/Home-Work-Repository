#include <vector>

// Leetcode 54

std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    int UP = 0, LEFT = 0, RIGHT = m - 1, DOWN = n - 1;
    std::vector<int> ans;
    ans.reserve(n * m);

    while (UP <= DOWN && LEFT <= RIGHT) {
        for (int col = LEFT; col <= RIGHT; ++col)
            ans.push_back(matrix[UP][col]);
        ++UP;

        for (int row = UP; row <= DOWN; ++row)
            ans.push_back(matrix[row][RIGHT]);
        --RIGHT;

        if (UP <= DOWN) {
            for (int col = RIGHT; col >= LEFT; --col)
                ans.push_back(matrix[DOWN][col]);
            --DOWN;
        }

        if (LEFT <= RIGHT) {
            for (int row = DOWN; row >= UP; --row)
                ans.push_back(matrix[row][LEFT]);
            ++LEFT;
        }
    }

    return ans;
}