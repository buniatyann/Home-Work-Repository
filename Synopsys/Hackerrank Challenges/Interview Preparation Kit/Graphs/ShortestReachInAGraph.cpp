#include <vector>
#include <queue>
#include <iostream>

class Graph {
public:
    /*
        Time O(V) 
        Space O(V)
        where V is the number of nodes in the graph
    */
    Graph(int n) {
        adj_list = std::vector<std::vector<int>>(n); // Initialize adjacency list
        this->n = n; // Store the number of nodes
    }
    
    /*
        Time O(1)
        Space O(1)
    */
    void add_edge(int u, int v) {
        adj_list[u].push_back(v); // Add v to the adjacency list of u
        adj_list[v].push_back(u); // Add u to the adjacency list of v (undirected graph)
    }
    
    /*
        Time O(V + E)
        Space O(V + E)
        where V is the number of nodes, and E is the number of edges
    */
    std::vector<int> shortest_reach(int start) {
        std::vector<int> shortest_path(n, -1); // Initialize all distances as -1 (unreachable)
        std::queue<int> q; // Queue for BFS
        q.push(start); // Push the starting node into the queue
        std::vector<bool> visited(n, false); // To track visited nodes
        visited[start] = true; // Mark the starting node as visited
        int curr_level = 1; // Current distance level (distance to neighboring nodes)

        // Perform BFS to find the shortest reach for each node
        while (!q.empty()) {
            int level_size = q.size(); // Get the number of nodes at the current level
            
            while (level_size--) {
                int curr_node = q.front(); // Get the current node from the queue
                q.pop(); // Remove the node from the queue
                
                for (int adj_val : adj_list[curr_node]) { // Traverse the adjacent nodes
                    if (!visited[adj_val]) { // If the node is not visited
                        shortest_path[adj_val] = curr_level * 6; // Set the shortest path distance
                        visited[adj_val] = true; // Mark as visited
                        q.push(adj_val); // Add the node to the queue
                    }
                }
            }
            
            ++curr_level; // Increase the current level for the next BFS iteration
        }
        
        return shortest_path; // Return the list of shortest paths
    }
    
private:
    std::vector<std::vector<int>> adj_list; // Adjacency list representation of the graph
    int n; // Number of nodes in the graph
};
