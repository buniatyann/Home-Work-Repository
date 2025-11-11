#ifndef AI_MODEL_HPP
#define AI_MODEL_HPP

#include <memory>
#include <string>
#include <iostream>

#include "../interface/IHardwareBackend.hpp"
#include "../interface/INeuralNet.hpp"

class AIModel {
public:
    AIModel(std::shared_ptr<IHardwareBackend> backend,
            std::shared_ptr<INeuralNet> network)
        : hardware(std::move(backend)), network(std::move(network)) {}

    void setBackend(std::shared_ptr<IHardwareBackend> backend) {
        hardware = std::move(backend);
        std::cout << "[AIModel] Hardware backend switched.\n";
    }

    void setNetwork(std::shared_ptr<INeuralNet> net) {
        network = std::move(net);
        std::cout << "[AIModel] Neural network model switched.\n";
    }

    void load(const std::string& modelName) {
        if (hardware) hardware->loadModel(modelName);
    }

    void runInference() const {
        if (hardware && network) {
            std::cout << "[AIModel] Starting inference...\n";
            hardware->run();
            network->run();
        }
    }

    void trainModel() const {
        if (network) {
            std::cout << "[AIModel] Starting training...\n";
            network->train();
        }
    }

    void showInfo() const {
        if (network) network->info();
    }

private:
    std::shared_ptr<IHardwareBackend> hardware;
    std::shared_ptr<INeuralNet> network;
};

#endif // AI_MODEL_HPP
