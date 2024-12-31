#include <iostream>
#include <vector>
#include <algorithm>

/*
    Time O(n + m * k)
    Space O(n + m)
    where n is the number of elements in the ranked list, m is the number of players, k is the number of distinct scores in ranked.
    veranayel
*/
std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player) {
    // Create a unique list of ranks from the ranked leaderboard
    std::vector<int> unique;
    unique.push_back(ranked[0]); // Add the first element as the first unique rank
    
    // Iterate through the ranked list to remove duplicates
    for (int i = 1; i < ranked.size(); ++i) {
        // Only add the element to 'unique' if it's not the same as the previous one
        if (ranked[i] != ranked[i - 1]) {
            unique.push_back(ranked[i]);  // Store only distinct scores in the unique vector
        }
    }

    // Initialize the answer vector and set j to the index of the last unique rank
    std::vector<int> ans;
    int j = unique.size() - 1;  // Start from the bottom of the unique ranks list

    // For each player's score, determine their rank
    for (int i = 0; i < player.size(); ++i) {
        // Move down the unique ranks list until we find the correct rank for the player's score
        while (j >= 0 && player[i] >= unique[j]) {
            --j;  // Move to the next lower rank (i.e., higher score)
        }
        
        // Rank is the index + 1 (since ranks are 1-based)
        // j + 2 because 'j' is 0-based, but ranks start from 1
        ans.push_back(j + 2);  // Append the calculated rank to the answer
    }

    return ans;  // Return the list of ranks for each player
}