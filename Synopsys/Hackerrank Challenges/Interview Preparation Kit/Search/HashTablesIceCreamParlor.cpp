#include <bits/stdc++.h>

// Time O(N) Space O(N)
void whatFlavors(std::vector<int>& cost, int money) {
    // Create a map to store the cost and their corresponding 1-based indices
    std::map<int, int> mp;

    // Populate the map with costs and their indices
    for (int i = 0; i < cost.size(); ++i) {
        mp[cost[i]] = i + 1; // Store the index as 1-based
    }

    // Iterate through the cost array to find two flavors
    for (int i = 0; i < cost.size(); ++i) {
        int diff = money - cost[i]; // Calculate the required complement

        // Check if the complement exists in the map and is not the same index
        if (mp.count(diff) && mp[diff] != i + 1) {
            // Print the indices of the two flavors
            std::cout << i + 1 << " " << mp[diff] << std::endl;
            return; // Exit the function after finding the first valid pair
        }
    }
}

// Time O(N) Space O(N)
void whatFlavors(std::vector<int>& cost, int money) {
    // Create a map to store the cost and their corresponding 1-based indices
    std::unordered_map<int, int> mp;

    // Populate the map with costs and their indices
    for (int i = 0; i < cost.size(); ++i) {
        mp[cost[i]] = i + 1; // Store the index as 1-based
    }

    // Iterate through the cost array to find two flavors
    for (int i = 0; i < cost.size(); ++i) {
        int diff = money - cost[i]; // Calculate the required complement

        // Check if the complement exists in the map and is not the same index
        if (mp.count(diff) && mp[diff] != i + 1) {
            // Print the indices of the two flavors
            std::cout << i + 1 << " " << mp[diff] << std::endl;
            return; // Exit the function after finding the first valid pair
        }
    }
}