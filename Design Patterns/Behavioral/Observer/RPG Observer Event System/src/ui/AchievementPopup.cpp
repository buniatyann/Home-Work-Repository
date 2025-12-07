#include "../../include/ui/AchievementPopup.hpp"
#include "../../include/game/GameEvents.hpp"

void AchievementPopup::onNotify(const std::any& data, int eventType) {
    if (eventType == static_cast<int>(EventType::ACHIEVEMENT_UNLOCKED)) {
        auto e = std::any_cast<AchievementEvent>(data);
        std::cout << "\nACHIEVEMENT UNLOCKED!\n"
                  << "  " << e.title << "\n"
                  << "  " << e.desc << "\n\n";
    }
}