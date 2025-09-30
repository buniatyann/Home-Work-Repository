#include "../../include/Characters/Elf.hpp"

Elf::Elf(const std::string& name, int damage, int health) {
    attributes.name = name;
    attributes.damage = damage;
    attributes.health = health;
}

Elf::Elf(const Elf& other) : ICharacter(other) {
    attributes = other.attributes;
}

Elf::Elf(Elf&& other) noexcept : ICharacter(std::move(other)) {
    attributes = std::move(other.attributes);
}

Elf::~Elf() {}

void Elf::giveDamage() const {
    std::cout << "Elf " << attributes.name << " gave fatal damage" << std::endl;
}

std::unique_ptr<ICharacter> Elf::clone() const {
    return std::make_unique<Elf>(*this);
}

void Elf::stats() const {
    std::cout << "Elf with a name: " << attributes.name 
              << ", damage: " << attributes.damage 
              << ", and health: " << attributes.health 
              << std::endl;
}
