#ifndef IWHEEL_HPP
#define IWHEEL_HPP

#include <string>
#include <memory>

class IWheel {
public:
    virtual ~IWheel() = default;
    virtual void install() const = 0;
    virtual std::unique_ptr<IWheel> clone() const = 0;
};

#endif // IWHEEL_HPP