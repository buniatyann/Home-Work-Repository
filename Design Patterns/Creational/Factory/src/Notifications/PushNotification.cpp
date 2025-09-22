#include "../../include/Notifications/PushNotification.hpp"
#include <iostream>

void PushNotification::send(const std::string& message) {
    std::cout << "Push Notification: " << message << std::endl;
}

std::unique_ptr<INotification> PushNotification::clone() const {
    return std::make_unique<PushNotification>(*this);
}