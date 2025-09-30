#include "../../include/Characters/Orc.hpp"

Orc::Orc(const std::string& name, int damage, int health) {
    attributes.name = name;
    attributes.damage = damage;
    attributes.health = health;
}

Orc::Orc(const Orc& other) : ICharacter(other) {
    attributes = other.attributes;
}

Orc::Orc(Orc&& other) noexcept : ICharacter(std::move(other)) {
    attributes = std::move(other.attributes);
}

Orc::~Orc() {}

void Orc::giveDamage() const {
    std::cout << "Orc " << attributes.name << " gave fatal damage" << std::endl;
}

std::unique_ptr<ICharacter> Orc::clone() const {
    return std::make_unique<Orc>(*this);
}

void Orc::stats() const {
    std::cout << "Orc with a name: " << attributes.name 
              << ", damage: " << attributes.damage 
              << ", and health: " << attributes.health 
              << std::endl;
}
