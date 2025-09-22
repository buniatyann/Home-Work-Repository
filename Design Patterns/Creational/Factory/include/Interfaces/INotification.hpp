#ifndef INOTIFICATION_HPP
#define iNOTIFICATION_HPP

#include <string>
#include <memory>

class INotification {
public:
    virtual ~INotification() = default;
    virtual void send(const std::string& message) = 0;
    virtual std::unique_ptr<INotification> clone() const = 0;
};

#endif // INOTIFICATION_HPP