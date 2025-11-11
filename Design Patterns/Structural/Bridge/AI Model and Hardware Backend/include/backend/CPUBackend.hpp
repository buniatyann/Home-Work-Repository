#ifndef CPU_BACKEND_HPP
#define CPU_BACKEND_HPP

#include "../interface/IHardwareBackend.hpp"
#include <iostream>
#include <string>

class CPUBackend : public IHardwareBackend {
public:
    explicit CPUBackend(const std::string& name) : name_(name) {}
    ~CPUBackend() override = default;

    void loadModel(const std::string& modelName) override {
        name_ = modelName;
        std::cout << "CPU backend is loading [MODEL]: " << modelName << std::endl;
    }

    void run() const override {
        std::cout << "CPU is running : " << name_ << std::endl;
    }

private:
    std::string name_;
};

#endif // CPU_BACKEND_HPP
