#include <vector>
#include <queue>

class Node {
public:
    std::vector<Node*> edges;  // List of neighboring nodes (edges)
    long color;                // The color associated with the node
    int id;                    // The ID of the node
    bool visited = false;      // Flag to mark if the node has been visited
    Node* source = nullptr;    // The source node from which this node was visited
    int distance = 0;          // The distance from the source node

    Node(int id, long color) {
        this->id = id;
        this->color = color;
    }
};

// Function to build the graph by creating nodes and connecting them using the given edges
std::vector<Node*> build_graph(int graph_nodes, std::vector<int>& graph_from, std::vector<int>& graph_to, std::vector<long>& ids) {
    int graphEdges = graph_from.size();
    std::vector<Node*> nodes(graph_nodes);  // Vector to store nodes

    // Create nodes and assign them their ID and color
    for (int i = 0; i < graph_nodes; i++) {
        nodes[i] = new Node(i + 1, ids[i]);
    }

    // Link nodes (edges)
    for (int i = 0; i < graphEdges; i++) {
        Node* from = nodes[graph_from[i] - 1];  // Node corresponding to graphFrom[i]
        Node* to = nodes[graph_to[i] - 1];      // Node corresponding to graphTo[i]
        from->edges.push_back(to);  // Add the edge from "from" to "to"
        to->edges.push_back(from);  // Add the edge from "to" to "from" (undirected graph)
    }

    return nodes;
}

// Breadth-First Search (BFS) to find the shortest path between nodes of a specific color
int bfs(std::vector<Node*>& nodes, long color) {
    std::queue<Node*> q;  // Queue for BFS

    // Initialize BFS by pushing all nodes with the matching color
    for (Node* node : nodes) {
        if (node->color != color) {
            continue;  // Skip nodes that do not have the desired color
        }

        node->visited = true;    // Mark the node as visited
        node->source = node;     // The node is its own source
        q.push(node);            // Push the node to the queue
    }

    // Optimization: if there is only one node of the desired color, there's no path to find
    if (q.size() == 1) {
        return -1;  // No path exists if only one node of the color is found
    }

    // Perform BFS
    while (!q.empty()) {
        Node* current = q.front();  // Get the current node from the queue
        q.pop();  // Remove the node from the queue

        // Check for the shortest path between nodes of the same color
        for (Node* neighbour : current->edges) {
            if (neighbour->source != nullptr && neighbour->source != current->source) {
                // If two nodes belong to different sources, return the distance between them
                return neighbour->distance + current->distance + 1;
            }
        }

        // Visit all neighbors and propagate the BFS
        for (Node* neighbour : current->edges) {
            if (neighbour->visited) {
                continue;  // Skip visited nodes
            }

            neighbour->visited = true;           // Mark the neighbor as visited
            neighbour->source = current->source; // Set the source for the neighbor
            neighbour->distance = current->distance + 1;  // Set the distance from the source
            q.push(neighbour);  // Push the neighbor to the queue
        }
    }

    return -1;  // Return -1 if no path was found
}

/*
    Time O(N + E)
    Space O(N + E)
    where N is the number of nodes, and E is the number of edges
*/
int findShortest(int graphNodes, std::vector<int>& graphFrom, std::vector<int>& graphTo, std::vector<long>& ids, int val) {
    // Build the graph from the given input data
    std::vector<Node*> nodes = build_graph(graphNodes, graphFrom, graphTo, ids);

    // Perform BFS on the graph to find the shortest path for the given color
    return bfs(nodes, val);
}