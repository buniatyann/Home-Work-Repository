#include "include/Router/RequestRouter.h"
#include "include/Bots/WeatherBot.h"
#include "include/Bots/BookingBot.h"
#include <iostream>

int main() {
    auto weatherBot = std::make_unique<WeatherBot>();
    auto bookingBot = std::make_unique<BookingBot>();
    RequestRouter router(std::move(weatherBot), std::move(bookingBot));

    std::string userId = "user1";
    std::cout << router.routeRequest(userId, "What's the weather in London?") << std::endl;
    std::cout << router.routeRequest(userId, "Book a flight to Paris") << std::endl;
    std::cout << router.routeRequest(userId, "What's the forecast?") << std::endl;
    std::cout << router.routeRequest(userId, "Set language to Spanish") << std::endl;
    std::cout << router.routeRequest(userId, "Weather in Madrid") << std::endl;

    return 0;
}