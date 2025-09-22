#include "../../include/Notification Factory/NotificationFactory.hpp"
#include "../../include/Notifications/EmailNotification.hpp"
#include "../../include/Notifications/SMSNotification.hpp"
#include "../../include/Notifications/PushNotification.hpp"
#include <stdexcept>

NotificationFactory::NotificationFactory() {
    prototypes_["Email"] = std::make_unique<EmailNotification>();
    prototypes_["SMS"] = std::make_unique<SMSNotification>();
    prototypes_["Push"] = std::make_unique<PushNotification>();
}

std::unique_ptr<INotification> NotificationFactory::createNotification(const std::string& type) const {
    auto it = prototypes_.find(type);
    if (it != prototypes_.end() && it->second) {
        return it->second->clone();
    }

    throw std::invalid_argument("Unknown notification type: " + type);
}

void NotificationFactory::send(const std::string& message, const std::string& type) {
    auto notification = createNotification(type);
    notification->send(message);
    history_.emplace_back(std::move(notification), type, message);
}

const std::vector<std::tuple<std::unique_ptr<INotification>, std::string, std::string>>& NotificationFactory::getHistory() const {
    return history_;
}

void NotificationFactory::replayNotification(size_t index) const {
    if (index >= history_.size()) {
        throw std::out_of_range("Invalid history index");
    }
    
    const auto& [notification, type, message] = history_[index];
    std::cout << "Replaying " << type << " notification: ";
    notification->send(message);
}