#ifndef INOTIFICATIONFACTORY_HPP
#define INOTIFICATIONFACTORY_HPP

#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include "INotification.hpp"

class INotificationFactory {
public:
    virtual ~INotificationFactory() = default;
    virtual std::unique_ptr<INotification> createNotification(const std::string& type) const = 0;
    virtual void send(const std::string& message, const std::string& type) = 0;
    virtual const std::vector<std::tuple<std::unique_ptr<INotification>, std::string, std::string>>& getHistory() const = 0;
    virtual void replayNotification(size_t index) const = 0;
};

#endif // INOTIFICATIONFACTORY_HPP