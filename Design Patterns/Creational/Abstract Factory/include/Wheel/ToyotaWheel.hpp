#ifndef TOYOTA_WHEEL_HPP
#define TOYOTA_WHEEL_HPP

#include "../Interfaces/IWheel.hpp"

class ToyotaWheel : public IWheel {
public:
    void install() const override;
    std::unique_ptr<IWheel> clone() const override;
};

#endif // TOYOTA_WHEEL_HPP