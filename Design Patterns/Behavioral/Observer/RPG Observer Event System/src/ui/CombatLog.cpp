#include "../../include/ui/CombatLog.hpp"
#include "../../include/game/GameEvents.hpp"

void CombatLog::onNotify(const std::any& data, int eventType) {
    switch (static_cast<EventType>(eventType)) {
        case EventType::ENEMY_DIED: {
            auto e = std::any_cast<EnemyDiedEvent>(data);
            std::cout << "[CombatLog] " << e.name << " defeated! +" << e.xp << " XP\n";
            break;
        }
        case EventType::PLAYER_LEVEL_UP:
            std::cout << "[CombatLog] PLAYER LEVELED UP!\n";
            break;
        default:
            break;
    }
}