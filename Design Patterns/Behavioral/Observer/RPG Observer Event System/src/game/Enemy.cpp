#include "../../include/game/Enemy.hpp"
#include "../../include/game/GameEvents.hpp"
#include <iostream>

Enemy::Enemy(std::string name, int health) : m_name(std::move(name)), m_health(health) {}

void Enemy::takeDamage(int dmg) {
    m_health -= dmg;
    if (m_health <= 0) {
        EnemyDiedEvent e{m_name, m_xpReward};
        notify(e, static_cast<int>(EventType::ENEMY_DIED));
        std::cout << m_name << " has been defeated!\n";
    }
}