#ifndef ACHIEVEMENT_POPUP_HPP
#define ACHIEVEMENT_POPUP_HPP

#include "../core/Observer.hpp"
#include <iostream>

class AchievementPopup : public Observer {
public:
    AchievementPopup() = default;
    void onNotify(const std::any& data, int eventType) override;
};

#endif // ACHIEVEMENT_POPUP_HPP