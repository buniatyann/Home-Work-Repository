#include "Graph.hpp"
#include <iostream>

int main() {
    Graph graph;
    
    Node* a = graph.add_node("A", 37.7749, -122.4194);
    Node* b = graph.add_node("B", 34.0522, -118.2437);
    Node* c = graph.add_node("C", 40.7128, -74.0060);

    graph.add_edge(*a, *b, 5.0);
    graph.add_edge(*b, *c, 3.0);
    graph.add_edge(*a, *c, 10.0);

    // Print adjacency list
    auto adj_list = graph.get_adj_list();
    std::cout << "Adjacency List:\n";
    for (const auto& [node_id, neighbors] : adj_list) {
        std::cout << "Node " << node_id << " -> ";
        for (const auto& [neighbor_id, weight] : neighbors) {
            std::cout << "(" << neighbor_id << ", " << weight << ") ";
        }
        std::cout << "\n";
    }

    // Print adjacency matrix
    auto adj_matrix = graph.get_adj_matrix();
    std::cout << "\nAdjacency Matrix:\n";
    for (const auto& row : adj_matrix) {
        for (double weight : row) {
            std::cout << (weight == std::numeric_limits<double>::infinity() ? "∞" : std::to_string(weight)) << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
