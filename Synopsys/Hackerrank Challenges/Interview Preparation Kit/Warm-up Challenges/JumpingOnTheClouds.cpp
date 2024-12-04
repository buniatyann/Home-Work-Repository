#include <vector>

/*
    Time O(n)
    Space O(1)
*/
int jumpingOnClouds(std::vector<int> c) {
    int min_jumps = 0;  // To track the minimum number of jumps
    int i = 0;  // The current position (starting at cloud 0)
    
    // Loop until we reach the second-to-last cloud
    while (i < c.size() - 1) {
        // Try to jump 2 clouds ahead if it's safe and within bounds
        if (i + 2 < c.size() && c[i + 2] == 0) {
            ++min_jumps;  // Increment jump count
            i += 2;  // Jump 2 clouds ahead
        }
        // Otherwise, jump 1 cloud ahead if possible
        else if (c[i + 1] == 0) {
            ++min_jumps;  // Increment jump count
            ++i;  // Jump 1 cloud ahead
        }
    }
    
    return min_jumps;  // Return the total number of jumps made
}
