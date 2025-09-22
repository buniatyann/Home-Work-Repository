#include <iostream>
#include "include/Notification Factory/NotificationFactory.hpp"

int main() {
    std::unique_ptr<INotificationFactory> factory = std::make_unique<NotificationFactory>();
    try {
        factory->send("Hello via Email!", "Email");
        factory->send("Hello via SMS!", "SMS");
        factory->send("Hello via Push!", "Push");
        std::cout << "\nReplaying notifications:\n";
        for (size_t i = 0; i < 3; ++i) {
            factory->replayNotification(i);
        }

        factory->send("Invalid", "Fax");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nNotification History:\n";
    for (const auto& [notification, type, message] : factory->getHistory()) {
        std::cout << "Type: " << type << ", Message: " << message << std::endl;
    }

    return 0;
}