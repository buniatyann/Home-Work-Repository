#include "PathFinder.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stdexcept>

std::vector<std::shared_ptr<Node>> PathFinder::dijkstra(std::shared_ptr<Node> start, std::shared_ptr<Node> goal) {
    std::unordered_map<std::shared_ptr<Node>, double, std::owner_less<>> distances;
    std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>, std::owner_less<>> previous;
    std::unordered_set<std::shared_ptr<Node>, std::owner_less<>> visited;

    auto compare = [](const std::pair<std::shared_ptr<Node>, double>& a, const std::pair<std::shared_ptr<Node>, double>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<std::shared_ptr<Node>, double>, std::vector<std::pair<std::shared_ptr<Node>, double>>, decltype(compare)> pq(compare);

    distances[start] = 0.0;
    pq.emplace(start, 0.0);

    while (!pq.empty()) {
        auto current = pq.top().first;
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (current == goal) break;

        for (const auto& [neighbor, weight] : current->get_neighbors()) {
            double new_dist = distances[current] + weight;
            if (!distances.count(neighbor) || new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                previous[neighbor] = current;
                pq.emplace(neighbor, new_dist);
            }
        }
    }

    return reconstruct_path(previous, start, goal);
}

std::vector<std::shared_ptr<Node>> PathFinder::a_star(std::shared_ptr<Node> start, std::shared_ptr<Node> goal) {
    std::unordered_map<std::shared_ptr<Node>, double, std::owner_less<>> g_score;
    std::unordered_map<std::shared_ptr<Node>, double, std::owner_less<>> f_score;
    std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>, std::owner_less<>> previous;
    std::unordered_set<std::shared_ptr<Node>, std::owner_less<>> visited;

    auto compare = [](const std::pair<std::shared_ptr<Node>, double>& a, const std::pair<std::shared_ptr<Node>, double>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<std::shared_ptr<Node>, double>, std::vector<std::pair<std::shared_ptr<Node>, double>>, decltype(compare)> open_set(compare);

    g_score[start] = 0.0;
    f_score[start] = haversine_heuristic(start, goal);
    open_set.emplace(start, f_score[start]);

    while (!open_set.empty()) {
        auto current = open_set.top().first;
        open_set.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (current == goal) break;

        for (const auto& [neighbor, weight] : current->get_neighbors()) {
            double tentative_g_score = g_score[current] + weight;
            if (!g_score.count(neighbor) || tentative_g_score < g_score[neighbor]) {
                previous[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + haversine_heuristic(neighbor, goal);
                open_set.emplace(neighbor, f_score[neighbor]);
            }
        }
    }
    return reconstruct_path(previous, start, goal);
}

double PathFinder::haversine_heuristic(std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
    const double R = 6371e3; // Earth radius in meters
    double lat1 = a->get_latitude() * M_PI / 180;
    double lat2 = b->get_latitude() * M_PI / 180;
    double dlat = (b->get_latitude() - a->get_latitude()) * M_PI / 180;
    double dlon = (b->get_longitude() - a->get_longitude()) * M_PI / 180;

    double x = std::sin(dlat / 2) * std::sin(dlat / 2) +
        std::cos(lat1) * std::cos(lat2) * std::sin(dlon / 2) * std::sin(dlon / 2);
    double y = 2 * std::atan2(std::sqrt(x), std::sqrt(1 - x));
    return R * y;
}

std::vector<std::shared_ptr<Node>> PathFinder::reconstruct_path(
    const std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>, std::owner_less<>>& previous,
    std::shared_ptr<Node> start, std::shared_ptr<Node> goal) {
    std::vector<std::shared_ptr<Node>> path;
    auto current = goal;
    while (current) {
        path.push_back(current);
        current = previous.count(current) ? previous.at(current) : nullptr;
        if (current == start) {
            path.push_back(start);
            break;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}
