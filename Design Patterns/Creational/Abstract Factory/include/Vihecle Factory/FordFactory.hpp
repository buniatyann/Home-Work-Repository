#ifndef FORD_FACTORY_HPP
#define FORD_FACTORY_HPP

#include "../Interfaces/IVehicleFactory.hpp"

class FordFactory : public IVehicleFactory {
public:
    std::unique_ptr<IEngine> createEngine() const override;
    std::unique_ptr<IWheel> createWheel() const override;
    void assembleSedan() const override;
    void assembleSUV() const override;
};

#endif // FORD_FACTORY_HPP