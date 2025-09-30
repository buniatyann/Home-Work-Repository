#include <iostream>
#include "include/Characters/CharacterRegistry.hpp"

int main() {
    CharacterRegistry registry;

    std::unique_ptr<ICharacter> dragon = registry.createCharacter("Dragon");
    std::unique_ptr<ICharacter> orc = registry.createCharacter("Orc");
    std::unique_ptr<ICharacter> elf = registry.createCharacter("Elf");

    std::cout << "\nDragon Stats and Action:" << std::endl;
    dragon->stats();
    dragon->giveDamage();

    std::cout << "\nOrc Stats and Action:" << std::endl;
    orc->stats();
    orc->giveDamage();

    std::cout << "\nElf Stats and Action:" << std::endl;
    elf->stats();
    elf->giveDamage();

    return 0;
}
