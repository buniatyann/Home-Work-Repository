#ifndef PUSHNOTIFICATION_HPP
#define PUSHNOTIFICATION_HPP

#include "../Interfaces/INotification.hpp"

class PushNotification : public INotification {
public:
    void send(const std::string& message) override;
    std::unique_ptr<INotification> clone() const override;
};

#endif // PUSHNOTIFICATION_HPP