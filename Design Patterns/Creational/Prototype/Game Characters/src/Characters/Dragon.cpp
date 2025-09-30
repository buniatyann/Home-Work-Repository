#include "../../include/Characters/Dragon.hpp"

Dragon::Dragon(const std::string& name, int damage, int health) {
    attributes.name = name;
    attributes.damage = damage;
    attributes.health = health;
}

Dragon::Dragon(const Dragon& other) : ICharacter(other) {
    attributes = other.attributes;
}

Dragon::Dragon(Dragon&& other) noexcept : ICharacter(std::move(other)) {
    attributes = std::move(other.attributes);
}

Dragon::~Dragon() {}

void Dragon::giveDamage() const {
    std::cout << "Dragon " << attributes.name << " gave fatal damage" << std::endl;
}

std::unique_ptr<ICharacter> Dragon::clone() const {
    return std::make_unique<Dragon>(*this);
}

void Dragon::stats() const {
    std::cout << "Dragon with a name: " << attributes.name 
              << ", damage: " << attributes.damage 
              << ", and health: " << attributes.health 
              << std::endl;
}
