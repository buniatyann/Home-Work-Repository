#include "include/Network/Network.hpp"
#include "include/Layer/Layer.hpp"
#include "include/Neuron/Neuron.hpp"
#include <memory>
#include <iostream>
#include <vector>

int main() {
    Network nn("SimpleNN");

    Layer layer1("InputLayer");
    layer1.addComponent(std::make_unique<Neuron>(std::vector<double>{0.5, 0.3}, 0.1));
    layer1.addComponent(std::make_unique<Neuron>(std::vector<double>{0.2, 0.4}, 0.2));

    Layer layer2("OutputLayer");
    layer2.addComponent(std::make_unique<Neuron>(std::vector<double>{0.7, 0.8}, 0.1));

    nn.addComponent(std::make_unique<Layer>(std::move(layer1)));
    nn.addComponent(std::make_unique<Layer>(std::move(layer2)));

    std::vector<double> input = {1.0, 2.0};
    std::cout << "Forward propagation:\n";
    auto output = nn.forward(input);
    std::cout << "Output: ";
    for (double val : output) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    std::cout << "\nBackward propagation:\n";
    nn.backward({0.5});

    return 0;
}