#include "../../include/Notifications/EmailNotification.hpp"
#include <iostream>

void EmailNotification::send(const std::string& message) {
    std::cout << "Email Notification: " << message << std::endl;
}

std::unique_ptr<INotification> EmailNotification::clone() const {
    return std::make_unique<EmailNotification>(*this);
}