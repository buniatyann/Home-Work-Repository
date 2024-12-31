#include <iostream>
#include <vector>

/*
    Time O(row * col)
    Space O(row * col)
    veranayel
*/
std::vector<std::string> bomberMan(int n, std::vector<std::string>& grid) {
    // Get the number of rows (R) and columns (C)
    int row = grid.size();
    int col = grid[0].size();
    
    // If n == 1, return the grid as is (no explosions)
    if (n == 1) {
        return grid;
    }
    
    // If n is even, return a grid of all 'O's (since all positions will be bombs)
    if (n % 2 == 0) {
        std::string fullRow(col, 'O'); // Create a row of 'O's of length C
        std::vector<std::string> fullGrid(row, fullRow); // Create R such rows
        return fullGrid;
    }
    
    // Convert grid to a 2D array (pad with extra row/column for easy boundary handling)
    std::vector<std::vector<int>> first(row + 2, std::vector<int>(col + 2, 0));  // Padding with 0 (no bomb)
    
    // Populate the padded grid where 1 indicates a bomb ('O')
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            first[i + 1][j + 1] = (grid[i][j] == 'O') ? 1 : 0;  // Bombs become 1, empty spaces 0
        }
    }
    
    // If n % 4 == 3 (this corresponds to rounds like 3, 7, 11,...)
    std::vector<std::vector<int>> third(row + 2, std::vector<int>(col + 2, 0));  // Grid for the first explosion
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (first[i][j] == 1) {  // If there is a bomb at position (i, j)
                // Mark the bomb and its adjacent cells as exploded (set to 1)
                third[i][j] = third[i + 1][j] = third[i][j + 1] = third[i - 1][j] = third[i][j - 1] = 1;
            }
        }
    }
    
    // If n % 4 == 3, the grid after the first round of explosions is our result
    if (n % 4 == 3) {
        std::vector<std::string> result;
        // Convert the third grid back to the result grid ('.' for exploded cells, 'O' for remaining bombs)
        for (int i = 1; i <= row; i++) {
            std::string row = "";
            for (int j = 1; j <= col; j++) {
                row += (third[i][j] == 1 ? '.' : 'O');
            }

            result.push_back(row);
        }

        return result;
    }
    
    // If n % 4 == 1 (this corresponds to rounds like 5, 9, 13,...)
    std::vector<std::vector<int>> fifth(row + 2, std::vector<int>(col + 2, 0));  // Grid for the second explosion
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (third[i][j] == 0) {  // If cell is not exploded in the first round
                // Mark the surrounding cells as exploded for the second round
                fifth[i][j] = fifth[i + 1][j] = fifth[i][j + 1] = fifth[i - 1][j] = fifth[i][j - 1] = 1;
            }
        }
    }
    
    // Convert the fifth grid back to the result grid ('.' for exploded cells, 'O' for remaining bombs)
    std::vector<std::string> result;
    for (int i = 1; i <= row; i++) {
        std::string row = "";
        for (int j = 1; j <= col; j++) {
            row += (fifth[i][j] == 1 ? '.' : 'O');
        }

        result.push_back(row);
    }

    return result;
}