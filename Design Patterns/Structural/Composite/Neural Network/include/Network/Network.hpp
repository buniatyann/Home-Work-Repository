#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "../Interface/INeuralComponent.hpp"
#include <string>
#include <vector>
#include <memory>

class Network : public INeuralComponent {
public:
    Network(const std::string& name);
    
    std::vector<double> forward(const std::vector<double>& vec) const override;
    void backward(const std::vector<double>& gradient) override;
    void addComponent(std::unique_ptr<INeuralComponent>&& component);

private:
    std::string name_;
    std::vector<std::unique_ptr<INeuralComponent>> layers_;
};

#endif // NETWORK_HPP