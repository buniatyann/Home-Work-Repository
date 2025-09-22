#ifndef TOYOTA_ENGINE_HPP
#define TOYOTA_ENGINE_HPP

#include "../Interfaces/IEngine.hpp"

class ToyotaEngine : public IEngine {
public:
    void install() const override;
    std::unique_ptr<IEngine> clone() const override;
};

#endif // TOYOTA_ENGINE_HPP