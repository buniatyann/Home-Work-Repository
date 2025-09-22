#ifndef IENGINE_HPP
#define IENGINE_HPP

#include <string>
#include <memory>

class IEngine {
public:
    virtual ~IEngine() = default;
    virtual void install() const = 0;
    virtual std::unique_ptr<IEngine> clone() const = 0;
};

#endif // IENGINE_HPP