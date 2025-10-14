#ifndef INEURAL_COMPONENT_HPP
#define INEURAL_COMPONENT_HPP

#include <memory>
#include <vector>
#include <string>
#include <iostream>

class INeuralComponenet {
public:
    virtual std::vector<double> forward(const std::vector<double>& vec) const = 0;
    virtual void backward(const std::vector<double>& gradient) = 0;
};

#endif // INEURAL_COMPONENT_HPP