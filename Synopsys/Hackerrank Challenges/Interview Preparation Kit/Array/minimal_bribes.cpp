#include <bits/stdc++.h>

void minimumBribes(std::vector<int> q) {
    int bribes = 0;
    bool chaotic = false;

    // Traverse from the last position to the first
    for (int i = q.size() - 1; i >= 0; --i) {
        // Check if the current position is more than two places ahead of the original position
        if (q[i] - (i + 1) > 2) {
            chaotic = true;
            break;
        }
        
        // Count how many times this person has been bribed
        for (int j = std::max(0, q[i] - 2); j < i; ++j) {
            if (q[j] > q[i]) {
                bribes++;
            }
        }
    }

    if (chaotic) {
        std::cout << "Too chaotic" << std::endl;
    } 
    
    else {
        std::cout << bribes << std::endl;
    }
    
}