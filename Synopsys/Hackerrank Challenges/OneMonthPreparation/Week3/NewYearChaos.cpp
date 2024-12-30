#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/*
    Time O(n)
    Space O(1)
*/
void minimumBribes(std::vector<int> q) {
    int bribes = 0;
    
    // Iterate from the end of the queue to the front
    for (int i = q.size() - 1; i >= 0; --i) {
        // Check if the person is more than two positions ahead of their original position
        if (q[i] - (i + 1) > 2) {
            std::cout << "Too chaotic" << std::endl;
            return; // Exit if "Too chaotic"
        }

        // Count the bribes by looking at positions that could have bribed the current person
        for (int j = std::max(0, q[i] - 2); j < i; ++j) {
            if (q[j] > q[i]) {
                ++bribes;
            }
        }
    }

    // Output the total number of bribes
    std::cout << bribes << std::endl;
}
