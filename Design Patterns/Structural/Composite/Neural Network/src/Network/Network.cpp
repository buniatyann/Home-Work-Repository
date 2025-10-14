#include "../../include/Network/Network.hpp"
#include <stdexcept>
#include <iostream>

Network::Network(const std::string& name) : name_(name) {}

std::vector<double> Network::forward(const std::vector<double>& vec) const {
    std::cout << "Layer... " + name_ + " Processing Forward" << std::endl;
    std::vector<double> output;
    for (const auto& component : layers_) {
        auto comp_output = component->forward(vec);
        output.insert(output.end(), comp_output.begin(), comp_output.end());
    }
 
    return output;
}

void Network::backward(const std::vector<double>& gradient) {
    std::cout << "Layer: " << name_ << " processing backward\n";
    if (gradient.size() != layers_.size()) {
        throw std::invalid_argument("Gradient size must match number of components");
    }

    size_t i = layers_.size() - 1;
    for (auto it = layers_.rbegin(); it != layers_.rend(); ++it) {
        (*it)->backward({gradient[i]});
        --i;
    }
}

void Network::addComponent(std::unique_ptr<INeuralComponent>&& component) {
    if (component) {
        layers_.push_back(std::move(component));
    }
}