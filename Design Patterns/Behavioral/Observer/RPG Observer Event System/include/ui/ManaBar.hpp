#ifndef MANA_BAR_HPP
#define MANA_BAR_HPP

#include "../core/Observer.hpp"
#include <iostream>

class Player;

class ManaBar : public Observer {
public:
    explicit ManaBar(Player* player);
    void onNotify(const std::any& data, int eventType) override;

private:
    Player* m_player;
};

#endif // MANA_BAR_HPP