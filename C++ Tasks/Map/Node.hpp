#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <cmath>
#include <functional>

constexpr double EARTH_RADIUS_KM = 6371.0;

class Node {
public:
    explicit Node(const std::string& name, double lon, double lat, std::size_t id = 0);

    std::pair<double, double> get_coordinates() const;
    std::string get_name() const;
    std::size_t get_id() const;
    const std::vector<std::pair<std::reference_wrapper<Node>, double>>& get_neighbors() const;

    void set_coordinates(double lon, double lat);
    void add_neighbor(Node& neighbor, double weight);
    double distance_to(const Node& other) const;

private:
    std::string name_;
    std::size_t id_;
    double longitude_;
    double latitude_;
    std::vector<std::pair<std::reference_wrapper<Node>, double>> neighbors_;
};

#endif // NODE_HPP
