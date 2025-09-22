#ifndef TOYOTA_FACTORY_HPP
#define TOYOTA_FACTORY_HPP

#include "../Interfaces/IVehicleFactory.hpp"

class ToyotaFactory : public IVehicleFactory {
public:
    std::unique_ptr<IEngine> createEngine() const override;
    std::unique_ptr<IWheel> createWheel() const override;
    void assembleSedan() const override;
    void assembleSUV() const override;
};

#endif // TOYOTA_FACTORY_HPP