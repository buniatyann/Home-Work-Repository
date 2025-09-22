#ifndef FORD_WHEEL_HPP
#define FORD_WHEEL_HPP

#include "../Interfaces/IWheel.hpp"

class FordWheel : public IWheel {
public:
    void install() const override;
    std::unique_ptr<IWheel> clone() const override;
};

#endif // FORD_WHEEL_HPP