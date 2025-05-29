#include "Graph.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <set>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

graph::graph() : max_vertex_(0) {}

graph::graph(const std::string& file_path, bool is_json) : max_vertex_(0) {
    if (is_json) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open JSON file: " + file_path);
        }

        json j;
        try {
            file >> j;
        } catch (const json::parse_error& e) {
            throw std::invalid_argument("Invalid JSON format: " + std::string(e.what()));
        }

        if (!j.contains("edges") || !j["edges"].is_array()) {
            throw std::invalid_argument("JSON must contain an 'edges' array");
        }

        for (const auto& edge : j["edges"]) {
            if (!edge.is_array() || edge.size() != 2) {
                throw std::invalid_argument("Each edge must be an array of two vertices");
            }
    
            int u, v;
            try {
                u = edge[0].get<int>();
                v = edge[1].get<int>();
            } catch (const json::type_error& e) {
                throw std::invalid_argument("Edge vertices must be integers");
            }
    
            add_edge(u, v);
        }

        file.close();
    } 
    else {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + file_path);
        }

        int n, m;
        if (!(file >> n >> m)) {
            throw std::invalid_argument("Invalid file format: expected vertex and edge count");
        }
        if (n < 0 || m < 0) {
            throw std::invalid_argument("Vertex and edge counts must be non-negative");
        }

        for (int i = 0; i < m; ++i) {
            int u, v;
            if (!(file >> u >> v)) {
                throw std::invalid_argument("Invalid file format: expected edge vertices");
            }
    
            add_edge(u, v);
        }

        file.close();
    }
    
    validate_graph();
}

graph::graph(const std::vector<std::pair<int, int>>& edges) : max_vertex_(0) {
    for (const auto& [u, v] : edges) {
        add_edge(u, v);
    }
    validate_graph();
}

graph::graph(const std::vector<std::vector<int>>& adj_matrix) : max_vertex_(0) {
    if (adj_matrix.empty()) 
        return;
        
    size_t n = adj_matrix.size();
    for (size_t i = 0; i < n; ++i) {
        if (adj_matrix[i].size() != n) {
            throw std::invalid_argument("Adjacency matrix must be square");
        }
    
        for (size_t j = 0; j < n; ++j) {
            if (adj_matrix[i][j] != 0 && adj_matrix[i][j] != 1) {
                throw std::invalid_argument("Adjacency matrix must contain only 0 or 1");
            }
            if (adj_matrix[i][j] == 1) {
                add_edge(i, j);
            }
        }
    }
    
    validate_graph();
}

void graph::add_edge(int u, int v) {
    if (u < 0 || v < 0) {
        throw std::invalid_argument("Vertex indices must be non-negative");
    }

    size_t max_index = std::max(static_cast<size_t>(u), static_cast<size_t>(v));
    if (max_index >= adj_.size()) {
        adj_.resize(max_index + 1);
    }
    
    max_vertex_ = std::max(max_vertex_, max_index);

    adj_[u].push_back(v);
    adj_[v].push_back(u);
}

std::vector<graph::Bridge> graph::bridge_Tarjan() {
    std::vector<Bridge> bridge;
    if (adj_.empty()) return bridge;

    std::vector<int> disc(max_vertex_ + 1, -1), low(max_vertex_ + 1, -1), parent(max_vertex_ + 1, -1);
    int time = 0;

    for (size_t vertex = 0; vertex <= max_vertex_; ++vertex) {
        if (!adj_[vertex].empty() && disc[vertex] == -1) {
            DFS_bridge(vertex, disc, low, parent, bridge, time);
        }
    }

    return bridge;
}

std::vector<int> graph::articulation_points() {
    std::vector<int> result;
    if (adj_.empty()) return result;

    std::vector<int> disc(max_vertex_ + 1, -1), low(max_vertex_ + 1, -1), parent(max_vertex_ + 1, -1);
    std::vector<bool> ap(max_vertex_ + 1, false);
    int time = 0;

    for (size_t vertex = 0; vertex <= max_vertex_; ++vertex) {
        if (!adj_[vertex].empty() && disc[vertex] == -1) {
            DFS_articulation(vertex, disc, low, parent, ap, time);
        }
    }

    for (size_t i = 0; i <= max_vertex_; ++i) {
        if (ap[i]) result.push_back(i);
    }
    
    return result;
}

std::vector<std::vector<int>> graph::get_adjacency_matrix() const {
    if (adj_.empty()) return {};

    std::vector<std::vector<int>> matrix(max_vertex_ + 1, std::vector<int>(max_vertex_ + 1, 0));

    for (size_t u = 0; u <= max_vertex_; ++u) {
        for (int v : adj_[u]) {
            matrix[u][v] = 1;
            matrix[v][u] = 1; // symmetry for undirected graph
        }
    }

    return matrix;
}

size_t graph::get_vertex_count() const {
    size_t count = 0;
    for (size_t i = 0; i <= max_vertex_; ++i) {
        if (!adj_[i].empty()) ++count;
    }
    
    return count;
}

size_t graph::get_edge_count() const {
    size_t count = 0;
    for (const auto& neighbors : adj_) {
        count += neighbors.size();
    }
    
    return count / 2;
}

bool graph::is_connected() const {
    if (adj_.empty()) return true;

    std::vector<bool> visited(max_vertex_ + 1, false);
    std::queue<int> q;
    size_t visited_count = 0;

    // Find first non-empty vertex
    size_t start = 0;
    while (start <= max_vertex_ && adj_[start].empty()) ++start;
    if (start > max_vertex_) return true;

    q.push(start);
    visited[start] = true;
    visited_count++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj_[u]) {
            if (!visited[v]) {
                visited[v] = true;
                visited_count++;
                q.push(v);
            }
        }
    }

    return visited_count == get_vertex_count();
}

void graph::export_to_dot(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    out << "graph G {\n";
    std::set<std::pair<int, int>> printed;

    for (size_t u = 0; u <= max_vertex_; ++u) {
        for (int v : adj_[u]) {
            int a = std::min(u, static_cast<size_t>(v));
            int b = std::max(u, static_cast<size_t>(v));
            if (printed.count({a, b}) == 0) {
                out << "    " << a << " -- " << b << ";\n";
                printed.insert({a, b});
            }
        }
    }

    out << "}\n";
    out.close();
}

void graph::clear() {
    adj_.clear();
    max_vertex_ = 0;
}

void graph::validate_graph() {
    for (size_t vertex = 0; vertex <= max_vertex_; ++vertex) {
        if (!adj_[vertex].empty()) {
            if (static_cast<int>(vertex) < 0) {
                throw std::invalid_argument("Vertex indices must be non-negative");
            }
    
            for (int neighbor : adj_[vertex]) {
                if (neighbor < 0) {
                    throw std::invalid_argument("Neighbor indices must be non-negative");
                }
                if (static_cast<size_t>(neighbor) > max_vertex_ || adj_[neighbor].empty()) {
                    throw std::invalid_argument("Graph must have bidirectional edges");
                }
                if (std::find(adj_[neighbor].begin(), adj_[neighbor].end(), vertex) == adj_[neighbor].end()) {
                    throw std::invalid_argument("Graph must have bidirectional edges");
                }
            }
        }
    }
}

void graph::DFS_bridge(int u, std::vector<int>& disc, std::vector<int>& low,
                       std::vector<int>& parent, std::vector<Bridge>& bridge, int& time) {
    disc[u] = low[u] = time++;
    for (int v : adj_[u]) {
        if (disc[v] == -1) {
            parent[v] = u;
            DFS_bridge(v, disc, low, parent, bridge, time);
            low[u] = std::min(low[u], low[v]);
            if (low[v] > disc[u]) {
                bridge.emplace_back(u, v);
            }
        } 
        else if (v != parent[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

void graph::DFS_articulation(int u, std::vector<int>& disc, std::vector<int>& low,
                             std::vector<int>& parent, std::vector<bool>& ap, int& time) {
    disc[u] = low[u] = time++;
    int children = 0;

    for (int v : adj_[u]) {
        if (disc[v] == -1) {
            parent[v] = u;
            ++children;
            DFS_articulation(v, disc, low, parent, ap, time);
            low[u] = std::min(low[u], low[v]);
            if (parent[u] == -1 && children > 1) {
                ap[u] = true;
            }
            if (parent[u] != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        } 
        else if (v != parent[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}