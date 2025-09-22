#ifndef NOTIFICATIONFACTORY_HPP
#define NOTIFICATIONFACTORY_HPP

#include "../Interfaces/INotificationFactory.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class NotificationFactory : public INotificationFactory {
public:
    NotificationFactory();
    std::unique_ptr<INotification> createNotification(const std::string& type) const override;
    void send(const std::string& message, const std::string& type) override;
    const std::vector<std::tuple<std::unique_ptr<INotification>, std::string, std::string>>& getHistory() const override;
    void replayNotification(size_t index) const override;

private:
    std::unordered_map<std::string, std::unique_ptr<INotification>> prototypes_;
    std::vector<std::tuple<std::unique_ptr<INotification>, std::string, std::string>> history_;
};

#endif // NOTIFICATIONFACTORY_HPP