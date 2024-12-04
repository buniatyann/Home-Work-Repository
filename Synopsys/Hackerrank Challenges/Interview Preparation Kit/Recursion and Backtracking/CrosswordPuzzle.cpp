#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

/*
    Time O(2^(W * S)), where W is the number of words, and S is the number of steps (or available positions) in the grid.
    Space O(SIZE * SIZE), for storing the grid, and O(W) for the unordered_set<string> storing the remaining words.
    veranayel
*/
const int SIZE = 10;
const int R_OFFSETS[] = { 0, 1 };  // Directions for Row (right, down)
const int C_OFFSETS[] = { 1, 0 };  // Directions for Column (right, down)

// Function to count how many cells are available for inserting a word in a given direction
int countInsertLength(const std::vector<std::vector<char>>& grid, int r, int c, int direction) {
    int prevR = r - R_OFFSETS[direction];
    int prevC = c - C_OFFSETS[direction];

    // Check if previous cell is blocked
    if (prevR >= 0 && prevR < SIZE && prevC >= 0 && prevC < SIZE && grid[prevR][prevC] != '+') {
        return 0;
    }

    // Count consecutive available cells in the given direction
    int insertLength = 0;
    while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && grid[r][c] != '+') {
        insertLength++;
        r += R_OFFSETS[direction];
        c += C_OFFSETS[direction];
    }
    return insertLength;
}

// Function to check if a word can be inserted at a given position and direction
bool canInsert(const std::vector<std::vector<char>>& grid, int r, int c, int direction, int insertLength, const std::string& word) {
    if (word.length() != insertLength) {
        return false;
    }

    for (int i = 0; i < word.length(); ++i) {
        int insertR = r + R_OFFSETS[direction] * i;
        int insertC = c + C_OFFSETS[direction] * i;
        if (grid[insertR][insertC] != '-' && grid[insertR][insertC] != word[i]) {
            return false;
        }
    }
    return true;
}

// Recursive function to attempt solving the crossword puzzle
std::vector<std::vector<char>> search(std::vector<std::vector<char>>& grid, std::unordered_set<std::string>& remainWords, int r, int c, int direction) {
    if (r == SIZE) {
        return grid;  // If we've filled all rows, return the grid
    }
    if (c == SIZE) {
        return search(grid, remainWords, r + 1, 0, 0);  // Move to the next row
    }
    if (direction == 2) {  // 2 directions: right (0) and down (1)
        return search(grid, remainWords, r, c + 1, 0);  // Move to the next column
    }

    int insertLength = countInsertLength(grid, r, c, direction);
    if (insertLength > 1) {
        for (const std::string& remainWord : std::vector<std::string>(remainWords.begin(), remainWords.end())) {
            if (canInsert(grid, r, c, direction, insertLength, remainWord)) {
                std::vector<int> insertOffsets;

                // Try inserting the word in the grid
                for (int insertOffset = 0; insertOffset < insertLength; ++insertOffset) {
                    int insertR = r + R_OFFSETS[direction] * insertOffset;
                    int insertC = c + C_OFFSETS[direction] * insertOffset;

                    if (grid[insertR][insertC] == '-') {
                        grid[insertR][insertC] = remainWord[insertOffset];
                        insertOffsets.push_back(insertOffset);
                    }
                }

                // Remove the word from the set of remaining words
                remainWords.erase(remainWord);

                // Recursively try to solve the grid
                std::vector<std::vector<char>> subResult = search(grid, remainWords, r, c, direction + 1);
                if (!subResult.empty()) {
                    return subResult;
                }

                // Backtrack by undoing the insertion
                remainWords.insert(remainWord);
                for (int insertOffset : insertOffsets) {
                    int insertR = r + R_OFFSETS[direction] * insertOffset;
                    int insertC = c + C_OFFSETS[direction] * insertOffset;
                    grid[insertR][insertC] = '-';
                }
            }
        }
        return {};  // Return an empty grid if no solution was found
    } else {
        return search(grid, remainWords, r, c, direction + 1);  // Try the next direction
    }
}

// Main function that orchestrates the crossword solution
std::vector<std::vector<char>> solve(std::vector<std::vector<char>>& grid, const std::vector<std::string>& words) {
    std::unordered_set<std::string> remainWords(words.begin(), words.end());
    return search(grid, remainWords, 0, 0, 0);  // Start solving from the top-left corner
}
