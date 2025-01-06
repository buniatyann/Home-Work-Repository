#include <vector>
#include <algorithm>
#include <iostream>

// This function performs a Depth First Search (DFS) to calculate the size of a connected region
// starting from the cell (i, j) in the grid.
int dfs(int i, int j, std::vector<std::vector<int>>& grid, const std::vector<std::pair<int, int>>& steps, int n, int m) {
    grid[i][j] = 2; // Mark the cell as visited by changing its value to 2 (since we assume 1 is part of the region)
    int area = 1; // Initialize the area for this region with the starting cell

    // Explore all 8 possible directions from the current cell
    for (const auto& step : steps) {
        int x = i + step.first; // Calculate the new x-coordinate
        int y = j + step.second; // Calculate the new y-coordinate

        // Check if the new coordinates (x, y) are within bounds and if the cell is part of the region (grid[x][y] == 1)
        if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 1) {
            // Recursively count the connected cells in the region and add their area to the current region's area
            area += dfs(x, y, grid, steps, n, m);
        }
    }

    return area; // Return the total area of the connected region
}

/*
    Time O(n * m)
    Space O(n * m)
*/
int maxRegion(std::vector<std::vector<int>>& grid) {
    int ans = 0; // Variable to store the size of the largest region found
    int n = grid.size(); // Number of rows in the grid
    int m = grid[0].size(); // Number of columns in the grid

    // Directions for exploring all 8 neighboring cells (up, down, left, right, and diagonals)
    std::vector<std::pair<int, int>> steps = { 
        {-1, -1}, {-1, 0}, {-1, 1}, 
        {0, -1}, {0, 1}, 
        {1, -1}, {1, 0}, {1, 1}
    };

    // Traverse every cell in the grid
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // If the cell is part of a region (contains a 1), start a DFS from this cell
            if (grid[i][j] == 1) {
                // Update the maximum area of the region found
                ans = std::max(ans, dfs(i, j, grid, steps, n, m));
            }
        }
    }

    return ans; // Return the largest connected region found
}