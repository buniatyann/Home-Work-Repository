#include "../../include/handlers/RateLimitHandler.hpp"
#include <iostream>

void RateLimitHandler::doHandle(Request& req, Response& res) {
    std::cout << "[RateLimit] Request allowed (simulated)\n";
}