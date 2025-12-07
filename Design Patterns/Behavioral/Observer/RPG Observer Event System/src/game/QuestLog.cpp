#include "../../include/game/QuestLog.hpp"
#include "../../include/game/Player.hpp"
#include "../../include/game/Enemy.hpp"
#include "../../include/game/GameEvents.hpp"
#include <iostream>

QuestLog::QuestLog() = default;

void QuestLog::subscribeTo(Player* player) {
    m_player = player;
    player->addObserver(shared_from_this());
}

void QuestLog::onNotify(const std::any& data, int eventType) {
    if (eventType == static_cast<int>(EventType::ENEMY_DIED)) {
        auto event = std::any_cast<EnemyDiedEvent>(data);
        if (event.name.find("Goblin") != std::string::npos) {
            completeQuest("Slay 5 Goblins");
        }
    }
}

void QuestLog::completeQuest(const std::string& questName) {
    std::cout << "QUEST COMPLETED: " << questName << "!\n";
    QuestEvent qe{questName, 100};
    onNotify(qe, static_cast<int>(EventType::QUEST_COMPLETED));
}