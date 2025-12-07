#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include "../core/Observer.hpp"
#include <iostream>

class Player;

class HealthBar : public Observer {
public:
    explicit HealthBar(Player* player);
    void onNotify(const std::any& data, int eventType) override;

private:
    Player* m_player;
};

#endif // HEALTH_BAR_HPP