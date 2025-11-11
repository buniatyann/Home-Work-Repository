#ifndef GPU_BACKEND_HPP
#define GPU_BACKEND_HPP

#include "../interface/IHardwareBackend.hpp"
#include <iostream>
#include <string>

class GPUBackend : public IHardwareBackend {
public:
    explicit GPUBackend(const std::string& name) : name_(name) {}
    ~GPUBackend() override = default;

    void loadModel(const std::string& modelName) override {
        name_ = modelName;
        std::cout << "GPU backend is loading [MODEL]: " << modelName << std::endl;
    }

    void run() const override {
        std::cout << "GPU is running : " << name_ << std::endl;
    }

private:
    std::string name_;
};

#endif // GPU_BACKEND_HPP
