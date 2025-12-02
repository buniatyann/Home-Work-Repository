#include "../include/WaiterSubsystem.hpp"

WaiterSubsystem::WaiterSubsystem() = default;

void WaiterSubsystem::takeOrder(const std::string& orderName) {
    std::cout << "Taking order " + orderName << std::endl;
}

void WaiterSubsystem::sendToKitchen() {
    std::cout << "Sends order to kitchen" << std::endl;
}

void WaiterSubsystem::serveCustomer() {
    std::cout << "Serving customer" << std::endl;
}

bool WaiterSubsystem::customerHappy() {
    return true;
}

void WaiterSubsystem::takeATip(unsigned long long tipSize = 20000) {
    if (customerHappy()) {
        std::cout  << "Customer is happy so is the waiter who recieved " << tipSize << std::endl;
    }
}

