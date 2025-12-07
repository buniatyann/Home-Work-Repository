#ifndef COMBATLOG_HPP
#define COMBATLOG_HPP

#include "../core/Observer.hpp"
#include <iostream>

class CombatLog : public Observer {
public:
    CombatLog() = default;
    void onNotify(const std::any& data, int eventType) override;
};

#endif // COMBATLOG_HPP