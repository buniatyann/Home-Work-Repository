#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <memory>
#include <iostream>
#include <string>

class ICharacter {
public:
    virtual ~ICharacter() = default;
    virtual void giveDamage() const = 0;
    virtual std::unique_ptr<ICharacter> clone() const = 0;
    virtual void stats() const = 0;

protected:
    struct Attributes {
        std::string name;
        int damage;
        int health;
    } attributes;
};

#endif // CHARACTER_HPP