#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "Edge.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

class Graph {
public:
    Graph() = default;
    
    Node* add_node(const std::string& name, double lon, double lat);
    void add_edge(Node& from, Node& to, double weight);

    Node* get_node(std::size_t id) const;
    size_t size() const;
    const std::vector<std::unique_ptr<Node>>& get_nodes() const;
    const std::vector<Edge>& get_edges() const;

    std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, double>>> get_adj_list() const;
    std::vector<std::vector<double>> get_adj_matrix() const;

private:
    std::vector<std::unique_ptr<Node>> nodes_;
    std::vector<Edge> edges_;
};

#endif // GRAPH_HPP
