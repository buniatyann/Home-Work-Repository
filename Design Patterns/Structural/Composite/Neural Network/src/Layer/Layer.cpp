#include "../../include/Layer/Layer.hpp"
#include <stdexcept>
#include <iostream>

Layer::Layer(const std::string& name) : name_(name) {}

std::vector<double> Layer::forward(const std::vector<double>& vec) const {
    std::cout << "Layer... " + name_ + " Processing Forward" << std::endl;
    std::vector<double> output;
    for (const auto& component : components_) {
        auto comp_output = component->forward(vec);
        output.insert(output.end(), comp_output.begin(), comp_output.end());
    }
    
    return output;
}

void Layer::backward(const std::vector<double>& gradient) {
    std::cout << "Layer: " << name_ << " processing backward\n";
    if (gradient.size() != components_.size()) {
        throw std::invalid_argument("Gradient size must match number of components");
    }

    size_t i = components_.size() - 1;
    for (auto it = components_.rbegin(); it != components_.rend(); ++it) {
        (*it)->backward({gradient[i]});
        --i;
    }
}

void Layer::addComponent(std::unique_ptr<INeuralComponent>&& component) {
    if (component) {
        components_.push_back(std::move(component));
    }
}