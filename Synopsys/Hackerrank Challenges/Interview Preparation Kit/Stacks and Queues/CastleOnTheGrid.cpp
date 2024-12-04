#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

/*
    Time O(n ^ 2)
    Space O(n ^ 2)
    veranayel
*/
int minimumMoves(std::vector<std::string> grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();  // size of the grid (n x n), assuming the grid is square
    
    // Directions: up, down, left, right
    // These represent the possible moves we can make in the grid
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // BFS queue (stores (x, y, moves))
    // Each element in the queue stores the current position (x, y) and the number of moves taken to reach that position
    std::queue<std::tuple<int, int, int>> q;
    
    // Start from the initial position (startX, startY) with 0 moves
    q.push({startX, startY, 0});
    
    // Visited matrix to keep track of visited positions
    // To avoid revisiting the same cells
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    visited[startX][startY] = true;  // Mark the starting position as visited
    
    // BFS loop: process the queue until it is empty
    while (!q.empty()) {
        int x, y, moves;
        std::tie(x, y, moves) = q.front();  // Get the current cell and the number of moves
        q.pop();  // Remove the current element from the queue
        
        // If we have reached the goal, return the number of moves
        if (x == goalX && y == goalY) {
            return moves;
        }
        
        // Explore all four directions (up, down, left, right)
        for (auto& dir : directions) {
            int dx = dir.first;  // Horizontal change
            int dy = dir.second; // Vertical change
            int nx = x, ny = y;
            
            // Move in the current direction as far as possible, until hitting a boundary or obstacle
            while (nx + dx >= 0 && nx + dx < n && ny + dy >= 0 && ny + dy < n && grid[nx + dx][ny + dy] == '.') {
                nx += dx;  // Move one step in the x direction
                ny += dy;  // Move one step in the y direction
                
                // If we haven't visited this cell yet, push it to the queue
                if (!visited[nx][ny]) {
                    visited[nx][ny] = true;  // Mark this cell as visited
                    q.push({nx, ny, moves + 1});  // Push the new position and increment the move count
                }
            }
        }
    }
    
    // If we exhaust the queue and don't find the goal, return -1 (no valid path exists)
    return -1;
}

