#ifndef ELF_HPP
#define ELF_HPP

#include "../Interface/ICharacter.hpp"
#include <memory>
#include <iostream>

class Elf : public ICharacter {
public:
    Elf(const std::string& name, int damage = 2048, int health = 400);

    Elf(const Elf& other);

    Elf(Elf&& other) noexcept;

    ~Elf() override;

    void giveDamage() const override;
    
    std::unique_ptr<ICharacter> clone() const override;

    void stats() const override;
};

#endif // ELF_HPP
