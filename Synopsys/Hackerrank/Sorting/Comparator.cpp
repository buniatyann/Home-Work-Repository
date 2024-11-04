#include <bits/stdc++.h>

struct Player {
    int score;
    std::string name;
};


/*
    Time O(1)
    Space O(1)
*/
class Checker {
public:
    // Comparator method to compare two Player objects
    static int comparator(const Player& a, const Player& b) {
        // Compare scores: higher score comes first
        if (a.score != b.score) {
            // Return 1 if a's score is greater (indicating a should come first),
            // Return -1 if b's score is greater (indicating b should come first)
            return (a.score > b.score) ? 1 : -1; // Descending order of score
        } 
        else if (a.score == b.score) {
            // If scores are equal, compare names in ascending order
            // Return 1 if a's name is lexicographically less than b's name
            // Return -1 otherwise
            return (a.name < b.name) ? 1 : -1; // Ascending order of name
        }
        
        // If both score and name are equal, return 0 (indicating they are equivalent)
        return 0;
    }
};
