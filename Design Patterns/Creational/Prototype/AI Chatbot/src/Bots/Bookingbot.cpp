#include "../../include/Bots/Bookingbot.h"
#include <regex>

BookingBot::BookingBot() {
    bot_name_ = "BookingBot";
    greeting_ = "Welcome to BookingBot! Book your services here.";
    setContext("currency", "USD");
}

std::unique_ptr<IChatbot> BookingBot::clone() const {
    return std::make_unique<BookingBot>(*this);
}

std::string BookingBot::respond(const std::string& request) {
    std::regex booking_regex("book.*to\\s+(\\w+)", std::regex::icase);
    std::smatch match;
    if (std::regex_search(request, match, booking_regex) && match.size() > 1) {
        last_booking_ = match[1];
        std::string currency = getContext("currency");
    
        return greeting_ + " Booking confirmed for " + last_booking_ + " (Currency: " + currency + ")";
    }
    else if (!last_booking_.empty()) {
        return "Details for your last booking to " + last_booking_;
    }
    
    return greeting_ + " Please specify a destination (e.g., 'book a flight to Paris').";
}