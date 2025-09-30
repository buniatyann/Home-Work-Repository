#ifndef CHARACTER_REGISTRY_HPP
#define CHARACTER_REGISTRY_HPP

#include "Dragon.hpp"
#include "Orc.hpp"
#include "Elf.hpp"
#include <unordered_map>
#include <stdexcept>
#include <memory>

class CharacterRegistry {
public:
    CharacterRegistry();

    void registerPrototype(const std::string& type, std::unique_ptr<ICharacter> prototype);

    std::unique_ptr<ICharacter> createCharacter(const std::string& type);

private:
    std::unordered_map<std::string, std::unique_ptr<ICharacter>> prototypes_;
};

#endif // CHARACTER_REGISTRY_HPP
