#include "Graph.hpp"

class MapAppllication{
private:
    void load_map_data(std::string filename){

    }

    void set_current_location(double long_, double lat_){

    }

    std::vector<Node*> find_shortest_path(Node* start, Node* end){
        path_find();
    }

public:
    Graph graph;
    Node* curr_location_;

    std::vector<Node*> path_find();
};