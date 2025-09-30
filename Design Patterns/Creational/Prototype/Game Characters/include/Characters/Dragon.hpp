#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "../Interface/ICharacter.hpp"
#include <memory>
#include <iostream>

class Dragon : public ICharacter {
public:
    Dragon(const std::string& name, int damage = 1024, int health = 500);

    Dragon(const Dragon& other);

    Dragon(Dragon&& other) noexcept;

    ~Dragon() override;

    void giveDamage() const override;

    std::unique_ptr<ICharacter> clone() const override;

    void stats() const override;
};

#endif // DRAGON_HPP
