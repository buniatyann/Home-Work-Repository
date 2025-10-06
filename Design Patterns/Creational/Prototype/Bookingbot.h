#ifndef BOOKINGBOT_H
#define BOOKINGBOT_H

#include "IChatbot.h"
#include <string>

class BookingBot : public IChatbot {
public:
    BookingBot();
    std::unique_ptr<IChatbot> clone() const override;
    std::string respond(const std::string& request) override;

private:
    std::string last_booking_;
};

#endif // BOOKINGBOT_H