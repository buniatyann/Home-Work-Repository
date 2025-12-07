#ifndef QUEST_LOG_HPP
#define QUEST_LOG_HPP

#include "../core/Observer.hpp"
#include "../core/Subject.hpp"
#include <string>
#include <map>

class Player;

class QuestLog : public Observer {
public:
    QuestLog();
    void onNotify(const std::any& data, int eventType) override;

    void subscribeTo(Player* player);

private:
    void completeQuest(const std::string& questName);

    Player* m_player = nullptr;
};

#endif // QUEST_LOG_HPP