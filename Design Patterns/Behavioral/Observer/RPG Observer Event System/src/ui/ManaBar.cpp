#include "../../include/ui/ManaBar.hpp"
#include "../../include/game/Player.hpp"
#include "../../include/game/GameEvents.hpp"

ManaBar::ManaBar(Player* player) : m_player(player) {
    player->addObserver(shared_from_this());
}

void ManaBar::onNotify(const std::any& data, int eventType) {
    if (eventType == static_cast<int>(EventType::MANA_CHANGED)) {
        auto e = std::any_cast<ManaEvent>(data);
        int percent = e.current * 20 / e.max;
        std::cout << " Mana : [" << std::string(percent, '*') 
                  << std::string(20 - percent, ' ') << "] "
                  << e.current << "/" << e.max << "\n";
    }
}