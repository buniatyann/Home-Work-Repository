#include "../../include/Notifications/SMSNotification.hpp"
#include <iostream>

void SMSNotification::send(const std::string& message) {
    std::cout << "SMS Notification: " << message << std::endl;
}

std::unique_ptr<INotification> SMSNotification::clone() const {
    return std::make_unique<SMSNotification>(*this);
}