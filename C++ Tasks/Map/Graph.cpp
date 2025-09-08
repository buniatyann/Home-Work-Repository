#include "Graph.hpp"
#include <limits>

Node* Graph::add_node(const std::string& name, double lon, double lat) {
    nodes_.push_back(std::make_unique<Node>(name, lon, lat, nodes_.size()));
    return nodes_.back().get();
}

void Graph::add_edge(Node& from, Node& to, double weight) {
    from.add_neighbor(to, weight);
    edges_.emplace_back(from, to, weight);
}

Node* Graph::get_node(std::size_t id) const {
    return (id < nodes_.size()) ? nodes_[id].get() : nullptr;
}

size_t Graph::size() const {
    return nodes_.size();
}

const std::vector<std::unique_ptr<Node>>& Graph::get_nodes() const {
    return nodes_;
}

const std::vector<Edge>& Graph::get_edges() const {
    return edges_;
}

std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, double>>> Graph::get_adj_list() const {
    std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, double>>> adj_list;
    
    for (const auto& edge : edges_) {
        adj_list[edge.get_from().get_id()].emplace_back(edge.get_to().get_id(), edge.get_weight());
    }
    
    return adj_list;
}

std::vector<std::vector<double>> Graph::get_adj_matrix() const {
    std::size_t n = nodes_.size();
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

    for (const auto& edge : edges_) {
        std::size_t from = edge.get_from().get_id();
        std::size_t to = edge.get_to().get_id();
        matrix[from][to] = edge.get_weight();
    }
    
    return matrix;
}
