#ifndef WEATHERBOT_H
#define WEATHERBOT_H

#include "IChatbot.h"
#include <string>

class WeatherBot : public IChatbot {
public:
    WeatherBot();
    std::unique_ptr<IChatbot> clone() const override;
    std::string respond(const std::string& request) override;

private:
    std::string last_location_;
};

#endif // WEATHERBOT_H