#include "Edge.hpp"

Edge::Edge(Node& from, Node& to, double weight) 
    : from_(from), to_(to), weight_(weight) {}

Node& Edge::get_from() const {
    return from_;
}

Node& Edge::get_to() const {
    return to_;
}

double Edge::get_weight() const {
    return weight_;
}
