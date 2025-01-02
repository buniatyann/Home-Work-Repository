#include <vector>
#include <algorithm>

/*
    Time O(n * log(n))
    Space O(n)
*/
int hackerlandRadioTransmitters(std::vector<int> x, int k) {
    // Sort the houses to process them in order
    std::sort(x.begin(), x.end());
    
    int n = x.size();
    int ans = 0;  // Number of transmitters placed
    int i = 0;    // Index to track the houses
    
    // Iterate through the houses
    while (i < n) {
        ++ans;  // We are placing a new transmitter
        
        // First, find the rightmost house that can be covered by the first transmitter
        int s = x[i];  // Start with the leftmost uncovered house
        while (i < n && x[i] <= s + k) {
            ++i;  // Move to the right to find the farthest house that can be covered
        }
        
        // Now, place the transmitter at the farthest house that can cover the range
        int p = x[i - 1];  // The transmitter should be placed at the farthest house in the range
        // Move the index to the first house that is NOT covered by the current transmitter
        while (i < n && x[i] <= p + k) {
            i++;
        }
    }
    
    return ans;
}