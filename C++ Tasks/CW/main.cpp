#include "Graph.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <cstdlib>  

void print_adjacency_matrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << "\nAdjacency Matrix:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        
        std::cout << "\n";
    }
}

void write_bridges_to_file(const std::vector<std::pair<int, int>>& bridges, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& [u, v] : bridges) {
        file << u << " " << v << "\n";
    }
}

void write_articulations_to_file(const std::vector<int>& articulation_points, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < articulation_points.size(); ++i) {
        file << articulation_points[i];
        if (i != articulation_points.size() - 1) {
            file << ", ";
        }
    }
}

int main() {
    std::string choice;
    std::cout << "Enter 1 to exit or any other key to continue: ";
    std::getline(std::cin, choice);
    if (choice == "1") {
        std::cout << "Exiting program.\n";
        return 0;
    }

    std::string file_path, file_type;
    std::cout << "Enter the path to the input graph file : ";
    std::getline(std::cin, file_path);
    if (file_path.empty()) {
        std::cerr << "Error: File path cannot be empty\n";
        return 1;
    }

    const std::string dot_output = "output.dot";
    const std::string bridges_file = "bridges.txt";
    const std::string articulation_file = "articulation.txt";

    // std::string pre_command = "python3 graph.py \"" + file_path + "\"";
    // std::system(pre_command.c_str());

    try {
        bool is_json = (file_type == "json");
        graph g(file_path, is_json);
        std::cout << "\nGraph loaded successfully.\n";

        std::cout << "Number of vertices: " << g.get_vertex_count() << "\n";
        std::cout << "Number of edges: " << g.get_edge_count() << "\n";
        std::cout << "Is graph connected? " << (g.is_connected() ? "Yes" : "No") << "\n";

        std::cout << "\nBridges in the graph:\n";
        auto bridges = g.bridge_Tarjan();
        if (bridges.empty()) {
            std::cout << "No bridges found.\n";
        } 
        else {
            for (const auto& [u, v] : bridges) {
                std::cout << u << " -- " << v << "\n";
            }
        }

        std::cout << "\nArticulation points:\n";
        auto articulation_points = g.articulation_points();
        if (articulation_points.empty()) {
            std::cout << "No articulation points found.\n";
        } 
        else {
            for (int v : articulation_points) {
                std::cout << v << "\n";
            }
        }

        print_adjacency_matrix(g.get_adjacency_matrix());

        g.export_to_dot(dot_output);
        write_bridges_to_file(bridges, bridges_file);
        write_articulations_to_file(articulation_points, articulation_file);

        std::cout << "\nDOT file written to: " << dot_output << "\n";
        std::cout << "Bridge list written to: " << bridges_file << "\n";
        std::cout << "Articulation points written to: " << articulation_file << "\n";

        // draw the graph with color corrections
        std::string post_command = "python3 graph.py \"" + file_path + "\" " + bridges_file + " " + articulation_file;
        std::system(post_command.c_str());

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
