#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int size[100001];  // Array to store the size of each group (city)
int parent[100001];  // Array to store the parent of each group (city)

// Find the representative (parent) of the group that the city belongs to
int find(int a) {
    if (a == parent[a]) {
        return a;  // If city a is its own parent, return a
    }

    return parent[a] = find(parent[a]);  // Path compression to improve future queries
}

// Union operation to group cities based on potential roads
void group(int a, int b) {
    a = find(a);  // Find the parent of city a
    b = find(b);  // Find the parent of city b
    
    if (a == b){ 
        return;  // If both cities are already in the same group, do nothing
    }
    if (size[a] < size[b]){ 
        std::swap(a, b);  // Ensure the larger group becomes the parent
    }

    parent[b] = a;  // Set the parent of b to be a
    size[a] += size[b];  // Update the size of the new parent group
}

/*
    Time O(n + m)
    Space O(n + m)
    where n is the number of cities and m is the number of roads.
    veranayel
*/
long roadsAndLibraries(int n, int c_lib, int c_road, std::vector<std::vector<int>> cities) {
    // If the cost of building a library is cheaper than or equal to building a road,
    // then it's better to build a library in each city because no roads are needed.
    if (c_lib <= c_road){ 
        return n * 1LL * c_lib;  // Cost for building n libraries
    }
    
    // Initialize the Size and Parent arrays for disjoint sets
    for (int i = 1; i <= n; i++) {
        size[i] = 1;  // Each city initially belongs to a group of size 1
        parent[i] = i;  // Initially, each city is its own parent (isolated)
    }
    
    // Group cities based on the roads (edges)
    for (const auto& c : cities) {
        group(c[0], c[1]);  // Connect city c[0] and city c[1]
    }
    
    // Map to track which city groups have been visited
    std::unordered_map<int, bool> umap;
    long long cost = 0;  // Variable to accumulate the total cost
    
    // Iterate through each city
    for (int i = 1; i <= n; i++) {
        int p = find(i);  // Find the parent (group leader) of city i
        
        if (umap[p]){ 
            continue; // If this group has already been visited, skip it
        } 

        cost += c_lib;  // Add cost for building a library in this group
        cost += ((size[p] - 1) * c_road);  // Add cost for roads to connect cities in this group
        umap[p] = 1;  // Mark this group as visited
    }
    
    return cost;  // Return the total cost of building libraries and roads
}