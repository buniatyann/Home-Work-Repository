#include "../../include/Characters/CharacterRegistry.hpp"

CharacterRegistry::CharacterRegistry() {
    registerPrototype("Dragon", std::make_unique<Dragon>("PrototypeDragon"));
    registerPrototype("Orc", std::make_unique<Orc>("PrototypeOrc"));
    registerPrototype("Elf", std::make_unique<Elf>("PrototypeElf"));
}

void CharacterRegistry::registerPrototype(const std::string& type, std::unique_ptr<ICharacter> prototype) {
    prototypes_[type] = std::move(prototype);
}

std::unique_ptr<ICharacter> CharacterRegistry::createCharacter(const std::string& type) {
    auto it = prototypes_.find(type);
    if (it != prototypes_.end()) {
        return it->second->clone();
    }

    throw std::runtime_error("Unknown character type: " + type);
}
