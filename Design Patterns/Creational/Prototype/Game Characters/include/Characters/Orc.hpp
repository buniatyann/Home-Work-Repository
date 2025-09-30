#ifndef ORC_HPP
#define ORC_HPP

#include "../Interface/ICharacter.hpp"
#include <memory>
#include <iostream>

class Orc : public ICharacter {
public:
    Orc(const std::string& name, int damage = 512, int health = 620);

    Orc(const Orc& other);

    Orc(Orc&& other) noexcept;

    ~Orc() override;

    void giveDamage() const override;
    
    std::unique_ptr<ICharacter> clone() const override;

    void stats() const override;
};

#endif // ORC_HPP
