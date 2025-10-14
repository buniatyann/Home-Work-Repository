#include "../../include/Neuron/Neuron.hpp"
#include <stdexcept>
#include <iostream>

Neuron::Neuron(const std::vector<double>& weights, double bias) : weights_(weights), bias_(bias) {}

std::vector<double> Neuron::forward(const std::vector<double>& vec) const {
    if (vec.size() != weights_.size()) {
        throw std::invalid_argument("Input size must match weights size");
    }

    double sum = bias_;
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += vec[i] * weights_[i];
    }
    
    return {relu(sum)};
}

void Neuron::backward(const std::vector<double>& gradient) {
    std::cout << "Neuron backward: gradient size = " << gradient.size() << "\n";
}

double Neuron::relu(double x) const {
    return x > 0 ? x : 0;
}