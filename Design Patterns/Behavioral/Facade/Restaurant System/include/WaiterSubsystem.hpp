#ifndef WAITER_SUBSYSTEM_HPP
#define WAITER_SUBSYSTEM_HPP

#include <string>
#include <iostream>

class WaiterSubsystem {
public:
    WaiterSubsystem();
    void takeOrder(const std::string& orderName);
    void sendToKitchen();
    void serveCustomer();
    void takeATip(unsigned long long tipSize);
private:
    bool customerHappy();
};

#endif // WAITER_SUBSYSTEM