#include "../../include/Router/RequestRouter.h"
#include <regex>
#include <algorithm>

RequestRouter::RequestRouter(std::unique_ptr<IChatbot> weatherBot, std::unique_ptr<IChatbot> bookingBot)
    : weatherBotPrototype_(std::move(weatherBot)), bookingBotPrototype_(std::move(bookingBot)) {
}

std::string RequestRouter::routeRequest(const std::string& userId, const std::string& request) {
    std::string lowerRequest = request;
    std::transform(lowerRequest.begin(), lowerRequest.end(), lowerRequest.begin(), ::tolower);

    std::unique_ptr<IChatbot> bot;
    if (std::regex_search(lowerRequest, std::regex("weather|forecast", std::regex::icase))) {
        bot = weatherBotPrototype_->clone();
        contextManager_.setContext(userId + "_type", "weather");
    }
    else if (std::regex_search(lowerRequest, std::regex("book|booking", std::regex::icase))) {
        bot = bookingBotPrototype_->clone();
        contextManager_.setContext(userId + "_type", "booking");
    }
    else {
        std::string context = contextManager_.getContext(userId + "_type");
        if (context == "weather") {
            bot = weatherBotPrototype_->clone();
        }
        else if (context == "booking") {
            bot = bookingBotPrototype_->clone();
        }
        else {
            return "Please specify 'weather' or 'booking' in your request.";
        }
    }

    return bot->respond(request);
}