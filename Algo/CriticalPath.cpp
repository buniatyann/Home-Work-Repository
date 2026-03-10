#include <algorithm>
#include <vector>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <limits>

// matrix[i][j] = {exists, weight} where exists != 0 means there is an edge i -> j with the given weight
// returns {path_indices, max_cost}
std::pair<std::vector<int>, double> critical_path(const std::vector<std::vector<std::pair<int, double>>>& matrix) {
    if (matrix.empty()) {
        throw std::runtime_error("adj matrix must be non-empty");
    }

    if (matrix.size() != matrix[0].size()) {
        throw std::runtime_error("must have the same size");
    }

    auto n = matrix.size();
    std::unordered_map<int, int> in_degree;
    for (size_t j = 0; j < n; ++j) {
        in_degree[j] = 0;
        for (size_t i = 0; i < n; ++i) {
            if (matrix[i][j].first)
                ++in_degree[j];
        }
    }

    std::set<int> zero_in;
    for (const auto& [node, deg] : in_degree) {
        if (deg == 0)
            zero_in.insert(node);
    }

    std::vector<int> topo_order;
    while (!zero_in.empty()) {
        auto it = zero_in.begin();
        int node = *it;
        zero_in.erase(it);
        topo_order.push_back(node);
        for (size_t j = 0; j < n; ++j) {
            if (matrix[node][j].first) {
                --in_degree[j];
                if (in_degree[j] == 0)
                    zero_in.insert(j);
            }
        }
    }

    // longest path via DP in topological order
    std::vector<double> dist(n, -std::numeric_limits<double>::infinity());
    std::vector<int> prev(n, -1);
    for (size_t node : topo_order) {
        if (dist[node] == -std::numeric_limits<double>::infinity())
            dist[node] = 0.0;

        for (size_t j = 0; j < n; ++j) {
            if (matrix[node][j].first) {
                double new_dist = dist[node] + matrix[node][j].second;
                if (new_dist > dist[j]) {
                    dist[j] = new_dist;
                    prev[j] = node;
                }
            }
        }
    }

    // the node with maximum distance
    size_t end_node = 0;
    for (size_t i = 1; i < n; ++i) {
        if (dist[i] > dist[end_node])
            end_node = i;
    }

    // reconstruct path
    std::vector<int> path;
    for (int node = end_node; node != -1; node = prev[node])
        path.push_back(node);

    std::reverse(path.begin(), path.end());
    return {path, dist[end_node]};
}
