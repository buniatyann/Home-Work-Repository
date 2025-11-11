#ifndef I_HARDWARE_BACKEND_HPP
#define I_HARDWARE_BACKEND_HPP

#include <string>
#include <memory>

class IHardwareBackend {
public:
    virtual ~IHardwareBackend() = default;
    virtual void loadModel(const std::string& modelName) = 0;
    virtual void run() const = 0;
};

#endif // I_HARDWARE_BACKEND_HPP
