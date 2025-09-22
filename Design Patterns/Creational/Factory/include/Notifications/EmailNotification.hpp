#ifndef EMAILNOTIFICATION_HPP
#define EMAILNOTIFICATION_HPP

#include "../Interfaces/INotification.hpp"

class EmailNotification : public INotification {
public:
    void send(const std::string& message) override;
    std::unique_ptr<INotification> clone() const override;
};

#endif // EMAILNOTIFICATION_HPP