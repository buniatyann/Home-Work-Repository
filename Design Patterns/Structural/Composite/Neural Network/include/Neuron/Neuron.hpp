#ifndef NEURON_HPP
#define NEURON_HPP

#include "../Interface/INeuralComponent.hpp"
#include <vector>
#include <string>

class Neuron : public INeuralComponent {
public:
    Neuron(const std::vector<double>& weights, double bias = 0.0);
    
    std::vector<double> forward(const std::vector<double>& vec) const override;
    void backward(const std::vector<double>& gradient) override;

private:
    std::vector<double> weights_;
    double bias_;
    
    double relu(double x) const;
};

#endif // NEURON_HPP