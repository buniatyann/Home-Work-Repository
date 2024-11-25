#include <vector>
#include <unordered_map>
#include <algorithm>

/*
    Time O(q) 
    Space O(n + q)
    where q is the number of queries and n is the number of unique people involved in the queries
    veranayel
*/
void init_cmp(std::unordered_map<int, int>& mp, int x, int y) {
    if (mp.find(x) == mp.end()) {
        mp[x] = x;  // Each person is their own parent initially
    }
    if (mp.find(y) == mp.end()) {
        mp[y] = y;
    }
}

// Initialize the 'component size' map to track the size of each group
void init_cc(std::unordered_map<int, int>& cc, int x, int y) {
    if (cc.find(x) == cc.end()) {
        cc[x] = 1;  // Initially, each person is in a group of size 1
    }
    if (cc.find(y) == cc.end()) {
        cc[y] = 1;
    }
}

// Find the root (representative) of the component to which 'x' belongs
int get_parent(std::unordered_map<int, int>& mp, int x) {
    while (mp[x] != x) {
        x = mp[x];  // Traverse up the tree to find the root
    }

    return x;
}

std::vector<int> maxCircle(std::vector<std::vector<int>>& queries) {
    std::unordered_map<int, int> mp;  // Map for tracking the parent of each person
    std::unordered_map<int, int> cc;  // Map for tracking the size of each component
    int max_gp = 0;  // Variable to track the largest group size
    std::vector<int> res;  // Store the result after each query
    
    for (const auto& q : queries) {
        // Initialize the Union-Find structures for each query
        init_cmp(mp, q[0], q[1]);
        init_cc(cc, q[0], q[1]);
        
        // Find the roots of both people in the query
        int p1 = get_parent(mp, q[0]);
        int p2 = get_parent(mp, q[1]);
        
        // If they are not in the same group, we need to unite them
        if (p1 != p2) {
            if (cc[p1] > cc[p2]) {
                mp[p2] = p1;  // Make p1 the parent of p2
                cc[p1] += cc[p2];  // Update the size of p1's group
            } 
            else {
                mp[p1] = p2;  // Make p2 the parent of p1
                cc[p2] += cc[p1];  // Update the size of p2's group
            }
            max_gp = std::max(max_gp, std::max(cc[p1], cc[p2]));  // Update the largest group size
        }
        
        // Append the current largest group size to the result
        res.push_back(max_gp);
    }

    return res;
}