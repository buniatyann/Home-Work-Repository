#ifndef EDGE_HPP
#define EDGE_HPP

#include "Node.hpp"

class Edge {
public:
    Edge(Node& from, Node& to, double weight);
    
    Node& get_from() const;
    Node& get_to() const;
    double get_weight() const;

private:
    Node& from_;
    Node& to_;
    double weight_;
};

#endif // EDGE_HPP
