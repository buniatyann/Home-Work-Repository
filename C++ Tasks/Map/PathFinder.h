#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Node.h"
#include <vector>
#include <unordered_map>
#include <memory>

class PathFinder {
public:
    static std::vector<std::shared_ptr<Node>> dijkstra(std::shared_ptr<Node> start, std::shared_ptr<Node> goal);
    static std::vector<std::shared_ptr<Node>> a_star(std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

private:
    static double haversine_heuristic(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
    static std::vector<std::shared_ptr<Node>> reconstruct_path(
        const std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>, std::owner_less<>>& previous,
        std::shared_ptr<Node> start, std::shared_ptr<Node> goal);
};

#endif // PATHFINDER_H
