#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <utility>
#include <fstream>
#include <string>

class graph {
public:
    using Bridge = std::pair<int, int>;

    graph();
    explicit graph(const std::string& file_path, bool is_json = false);
    graph(const std::vector<std::pair<int, int>>& edges);
    graph(const std::vector<std::vector<int>>& adj_matrix);
    graph(const graph& other) = default;
    graph(graph&& other) noexcept = default;

    graph& operator=(const graph& other) = default;
    graph& operator=(graph&& other) noexcept = default;

    ~graph() = default;

    void add_edge(int u, int v);
    void clear();

    std::vector<Bridge> bridge_Tarjan();
    std::vector<int> articulation_points();
    std::vector<std::vector<int>> get_adjacency_matrix() const;
    size_t get_vertex_count() const;
    size_t get_edge_count() const;
    bool is_connected() const;
    void export_to_dot(const std::string& filename) const;

private:
    std::vector<std::vector<int>> adj_;
    size_t max_vertex_;

    void validate_graph();
    void DFS_bridge(int u, std::vector<int>& disc, std::vector<int>& low,
                    std::vector<int>& parent, std::vector<Bridge>& bridge, int& time);
    void DFS_articulation(int u, std::vector<int>& disc, std::vector<int>& low,
                          std::vector<int>& parent, std::vector<bool>& ap, int& time);
};

#endif // GRAPH_HPP