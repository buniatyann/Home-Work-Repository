#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

int find(int x, std::unordered_map<int, int>& parent) {
    // If the element does not have a parent, initialize it as its own parent (it is its own root)
    if (parent.find(x) == parent.end()) {
        parent[x] = x; 
    }

    // If the current element is not the root, find the root recursively and compress the path
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent); // Path compression
    }

    // Return the root of the set
    return parent[x];
}

// Union function to union two sets with size optimization and checking if roads are connecting red cities
// If both cities connected by a road have machines, return the cost to destroy the road (since we want to disconnect them)
int union_sets(const std::vector<int>& road, std::vector<bool>& red, std::vector<int>& size, std::unordered_map<int, int>& parent) {
    // Find the roots of the two cities connected by the road
    int root1 = find(road[0], parent);
    int root2 = find(road[1], parent);

    // If both cities are red (i.e., both have machines), return the cost of destroying the road
    if (red[root1] && red[root2]) {
        return road[2]; // This road needs to be destroyed to disconnect the machines
    }

    // If the two cities are in different sets, perform the union operation
    if (root1 != root2) {
        // Union by size: attach the smaller tree to the larger one for optimal performance
        if (size[root1] > size[root2]) {
            std::swap(root1, root2); // Swap to ensure root1 is the smaller tree
        }
        
        // Attach root1 to root2 (root2 becomes the root of the union)
        parent[root1] = root2; 
        size[root2] += size[root1]; // Update the size of the new root
    }

    // Mark the combined set as red if either of the two roots was red (indicating that the set now has a machine)
    red[root1] = red[root1] | red[root2];
    red[root2] = red[root2] | red[root1];

    return 0; // No cost to destroy road if it does not connect two cities with machines
}

/*
    Time O(ElogE+E⋅α(N)) where E is the number of roads, N is the number of cities, and α is the inverse Ackermann function.
    Space O(N + E) for the parent map and size array.
*/
int minTime(std::vector<std::vector<int>>& roads, std::vector<int>& machines) {
    // Sort roads by destruction time in descending order so that we process the most expensive roads first
    std::sort(roads.begin(), roads.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[2] > b[2]; // Sort by the 3rd element (destruction time) in descending order
    });

    // Initialize the Union-Find structure (parent map)
    std::unordered_map<int, int> parent;

    int n = roads.size() + 1; // Number of cities (since we have `n-1` roads)
    std::vector<bool> red(n, false); // Array to mark cities that have machines (red = true)

    // Mark cities with machines (from the input list `machines`)
    for (int machine : machines) {
        red[machine] = true;
    }

    std::vector<int> size(n, 1); // Size of each set (initially 1 for each city)
    int total_cost = 0; // Initialize the total cost

    // Process each road (in order of descending destruction time)
    for (const std::vector<int>& road : roads) {
        total_cost += union_sets(road, red, size, parent); // Attempt to union the cities connected by the road
    }

    return total_cost; // Return the total cost of destroying roads to disconnect the machines
}