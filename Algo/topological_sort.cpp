#include <vector>
#include <set>
#include <stdexcept>
#include <unordered_map>

template <typename T>
std::vector<int> topological_sort(const std::vector<std::vector<T>>& matrix) {
    if (matrix.empty()) {
        throw std::runtime_error("adj matrix must be non-empty");
    }

    if (matrix.size() != matrix[0].size()) {
        throw std::runtime_error("must have the same size");
    }

    int n = matrix.size();

    std::unordered_map<int, int> nameToNeighborCount;
    for (int j = 0; j < n; ++j) {
        nameToNeighborCount[j] = 0;
        for (int i = 0; i < n; ++i) {
            nameToNeighborCount[j] += matrix[i][j];
        }
    }

    std::unordered_map<int, std::set<int>> nameToNeighbors;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j]) {
                nameToNeighbors[i].insert(j);
            }
        }
    }

    std::set<int> zeroNeighborCountNames;
    for (const auto& [name, neighborCount] : nameToNeighborCount) {
        if (neighborCount == 0) {
            zeroNeighborCountNames.insert(name);
        }
    }

    std::vector<int> result;
    while (!zeroNeighborCountNames.empty()) {
        auto it = zeroNeighborCountNames.begin();
        int name = *it;
        zeroNeighborCountNames.erase(it);
        result.push_back(name);
        for (const auto& neighbor : nameToNeighbors[name]) {
            --nameToNeighborCount[neighbor];
            if (nameToNeighborCount[neighbor] == 0) {
                zeroNeighborCountNames.insert(neighbor);
            }
        }
    }

    return result;
}
