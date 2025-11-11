#ifndef TPU_BACKEND_HPP
#define TPU_BACKEND_HPP

#include "../interface/IHardwareBackend.hpp"
#include <iostream>
#include <string>

class TPUBackend : public IHardwareBackend {
public:
    explicit TPUBackend(const std::string& name) : name_(name) {}
    ~TPUBackend() override = default;

    void loadModel(const std::string& modelName) override {
        name_ = modelName;
        std::cout << "TPU backend is loading [MODEL]: " << modelName << std::endl;
    }

    void run() const override {
        std::cout << "TPU is running : " << name_ << std::endl;
    }

private:
    std::string name_;
};

#endif // TPU_BACKEND_HPP
