#ifndef GRAPH_MODEL_HPP
#define GRAPH_MODEL_HPP

#include "../interface/INeuralNet.hpp"
#include <iostream>

class GraphModel : public INeuralNet {
public:
    ~GraphModel() override = default;

    void run() override {
        std::cout << "Graph Model is running" << std::endl;
    }

    void info() override {
        std::cout << "Graph Model" << std::endl;
    }

    void train() override {
        std::cout << "Graph Model Generator is training" << std::endl;
    }
};

#endif // GRAPH_MODEL_HPP
