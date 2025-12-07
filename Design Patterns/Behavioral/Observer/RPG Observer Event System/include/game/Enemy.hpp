#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../core/Subject.hpp"
#include <string>

class Enemy : public Subject {
public:
    Enemy(std::string name, int health = 80);

    void takeDamage(int dmg);
    bool isDead() const { return m_health <= 0; }
    std::string getName() const { return m_name; }
    int getXPReward() const { return m_xpReward; }

private:
    std::string m_name;
    int m_health;
    int m_xpReward = 150;
};

#endif // ENEMY_HPP