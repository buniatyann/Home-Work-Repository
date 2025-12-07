#include "../../include/game/Player.hpp"
#include "../../include/game/GameEvents.hpp"
#include <iostream>

Player::Player(std::string name) : m_name(std::move(name)) {}

void Player::takeDamage(int amount) {
    m_health = std::max(0, m_health - amount);
    HealthEvent e{m_health, m_maxHealth};
    notify(e, static_cast<int>(EventType::HEALTH_CHANGED));
    if (m_health <= 0) 
        std::cout << m_name << " died!\n";
}

void Player::heal(int amount) {
    m_health = std::min(m_maxHealth, m_health + amount);
    HealthEvent e{m_health, m_maxHealth};
    notify(e, static_cast<int>(EventType::HEALTH_CHANGED));
}

void Player::consumeMana(int amount) {
    m_mana = std::max(0, m_mana - amount);
    ManaEvent e{m_mana, m_maxMana};
    notify(e, static_cast<int>(EventType::MANA_CHANGED));
}

void Player::restoreMana(int amount) {
    m_mana = std::min(m_maxMana, m_mana + amount);
    ManaEvent e{m_mana, m_maxMana};
    notify(e, static_cast<int>(EventType::MANA_CHANGED));
}

void Player::gainXP(int xp) {
    m_xp += xp;
    std::cout << m_name << " gained " << xp << " XP!\n";
    if (m_xp > m_level * 300) {
        ++m_level;
        notify(std::monostate{}, static_cast<int>(EventType::PLAYER_LEVEL_UP));
        AchievementEvent ach{"Level Up!", "Reached level " + std::to_string(m_level)};
        notify(ach, static_cast<int>(EventType::ACHIEVEMENT_UNLOCKED));
    }
}