#ifndef KITCHEN_SUBSYSTEM_HPP
#define KITCHEN_SUBSYSTEM_HPP

#include <iostream>
#include <memory>
#include <string>


class KitchenSubsystem {
public:
    KitchenSubsystem();
    void prepareMeal(const std::string& name) const;
    void callWaiter() const;
    void giveComplementTo() const;
    void washDishes() const;
};

#endif // KITCHEN_SUBSYSTEM_HPP