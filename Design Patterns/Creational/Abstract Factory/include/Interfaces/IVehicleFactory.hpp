#ifndef IVEHICLEFACTORY_HPP
#define IVEHICLEFACTORY_HPP

#include "IEngine.hpp"
#include "IWheel.hpp"
#include <memory>
#include <string>

class IVehicleFactory {
public:
    virtual ~IVehicleFactory() = default;
    virtual std::unique_ptr<IEngine> createEngine() const = 0;
    virtual std::unique_ptr<IWheel> createWheel() const = 0;
    virtual void assembleSedan() const = 0;
    virtual void assembleSUV() const = 0;
};

#endif // IVEHICLEFACTORY_HPP