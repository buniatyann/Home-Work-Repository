#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../core/Subject.hpp"
#include <string>
#include <variant>

class Player : public Subject {
public:
    Player(std::string name = "Hero");

    void takeDamage(int amount);
    void heal(int amount);
    void consumeMana(int amount);
    void restoreMana(int amount);
    void gainXP(int xp);

    int getHealth() const { return m_health; }
    int getMaxHealth() const { return m_maxHealth; }
    int getMana() const { return m_mana; }
    int getMaxMana() const { return m_maxMana; }
    int getLevel() const { return m_level; }

private:
    std::string m_name;
    int m_health = 100, m_maxHealth = 100;
    int m_mana = 50, m_maxMana = 50;
    int m_xp = 0, m_level = 1;
};

#endif // PLAYER_HPP