#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/*
    Time O(n*log(n))
    Space O(1)
*/
int getMinimumCost(int k, std::vector<int> c) {
    // Base case: If the number of friends is equal to the number of costs, each friend gets exactly one item
    if (k == c.size()) {
        return std::accumulate(c.begin(), c.end(), 0);  // Sum of all costs
    }

    // Sort the costs in ascending order to prioritize distributing the cheaper items first
    std::sort(c.begin(), c.end());

    int ans = 0;  // Variable to hold the total cost
    int count = 0;  // Variable to track the number of items already assigned to friends

    // Iterate through the sorted costs array, starting from the most expensive items
    for (int i = c.size() - 1; i >= 0; --i) {
        // The cost for each item is multiplied by how many items the friend has already taken
        // Every k-th item increases the cost for the next friend by one more time
        ans += c[i] * (count / k + 1);  // `(count / k + 1)` increases for each friend's turn
        count++;  // Increase the count of assigned items
    }

    return ans;  // Return the total minimized cost
}
