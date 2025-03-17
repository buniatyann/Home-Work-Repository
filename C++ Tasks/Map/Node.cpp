#include "Node.hpp"

Node::Node(const std::string& name, double lon, double lat, std::size_t id)
    : name_(name), id_(id), longitude_(lon), latitude_(lat) {}

std::pair<double, double> Node::get_coordinates() const {
    return {longitude_, latitude_};
}

std::string Node::get_name() const {
    return name_;
}

std::size_t Node::get_id() const {
    return id_;
}

const std::vector<std::pair<std::reference_wrapper<Node>, double>>& Node::get_neighbors() const {
    return neighbors_;
}

void Node::set_coordinates(double lon, double lat) {
    longitude_ = lon;
    latitude_ = lat;
}

void Node::add_neighbor(Node& neighbor, double weight) {
    neighbors_.emplace_back(neighbor, weight);
}

double Node::distance_to(const Node& other) const {
    double lat1 = latitude_ * M_PI / 180.0;
    double lon1 = longitude_ * M_PI / 180.0;
    double lat2 = other.latitude_ * M_PI / 180.0;
    double lon2 = other.longitude_ * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}
