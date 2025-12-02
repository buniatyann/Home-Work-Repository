#include "../include/KitchenSubsystem.hpp"

KitchenSubsystem::KitchenSubsystem() = default;

void KitchenSubsystem::prepareMeal(const std::string& meal) const {
    std::cout << "Kitchen is preparing " + meal << std::endl;
}

void KitchenSubsystem::callWaiter() const {
    std::cout << "Meal is ready, kitchen calls for a waiter" << std::endl;
}

void KitchenSubsystem::giveComplementTo() const {
    std::cout << "You're beautiful, so eat this xorovats" << std::endl;
}

void KitchenSubsystem::washDishes() const {
    std::cout << "The most uninteresting or janjyal part" << std::endl;
}