#include "../../include/ui/HealthBar.hpp"
#include "../../include/game/Player.hpp"
#include "../../include/game/GameEvents.hpp"
#include <memory>

HealthBar::HealthBar(Player* player) : m_player(player) {
    player->addObserver(shared_from_this());
}

void HealthBar::onNotify(const std::any& data, int eventType) {
    if (eventType == static_cast<int>(EventType::HEALTH_CHANGED)) {
        auto e = std::any_cast<HealthEvent>(data);
        int percent = e.current * 20 / e.max;
        std::cout << "Health: [" << std::string(percent, '#') 
                  << std::string(20 - percent, ' ') << "] "
                  << e.current << "/" << e.max << "\n";
    }
}