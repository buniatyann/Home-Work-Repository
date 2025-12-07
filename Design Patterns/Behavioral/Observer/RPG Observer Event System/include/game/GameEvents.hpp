#ifndef GAMEEVENTS_HPP
#define GAMEEVENTS_HPP

#include <string>

enum class EventType {
    HEALTH_CHANGED = 1,
    MANA_CHANGED,
    ENEMY_DIED,
    QUEST_PROGRESS,
    QUEST_COMPLETED,
    ACHIEVEMENT_UNLOCKED,
    PLAYER_LEVEL_UP
};

struct HealthEvent { int current; int max; };
struct ManaEvent   { int current; int max; };
struct EnemyDiedEvent { std::string name; int xp; };
struct QuestEvent { std::string questName; int progress; };
struct AchievementEvent { std::string title; std::string desc; };

#endif // GAMEEVENTS_HPP