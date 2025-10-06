#include "../../include/Bots/Weatherbot.h"
#include "regex"

WeatherBot::WeatherBot() {
    bot_name_ = "WeatherBot";
    greeting_ = "Welcome to WeatherBot! Ask about the weather anywhere.";
    setContext("language", "en");
}

std::unique_ptr<IChatbot> WeatherBot::clone() const {
    return std::make_unique<WeatherBot>(*this);
}

std::string WeatherBot::respond(const std::string& request) {
    std::regex location_regex("weather.*in\\s+(\\w+)", std::regex::icase);
    std::smatch match;
    if (std::regex_search(request, match, location_regex) && match.size() > 1) {
        last_location_ = match[1];
        std::string lang = getContext("language");
       
        return greeting_ + " Forecast for " + last_location_ + " (Language: " + lang + ")";
    }
    else if (!last_location_.empty()) {
        return "Latest forecast for " + last_location_;
    }

    return greeting_ + " Please specify a location (e.g., 'weather in London').";
}