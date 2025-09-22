#ifndef FORD_ENGINE_HPP
#define FORD_ENGINE_HPP

#include "../Interfaces/IEngine.hpp"

class FordEngine : public IEngine {
public:
    void install() const override;
    std::unique_ptr<IEngine> clone() const override;
};

#endif // FORD_ENGINE_HPP