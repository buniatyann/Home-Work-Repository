#include "../include/RestFacade.hpp"

RestFacade::RestFacade()
    : kitchen_(std::make_unique<KitchenSubsystem>()),
      waiter_(std::make_unique<WaiterSubsystem>()) {}

void RestFacade::orderFood(const std::string& name) {
    waiter_->takeOrder(name);
    waiter_->sendToKitchen();
    kitchen_->prepareMeal(name);
    kitchen_->callWaiter();
    waiter_->serveCustomer();
    waiter_->takeATip(20000000);  
    kitchen_->giveComplementTo();
    kitchen_->washDishes();
}
