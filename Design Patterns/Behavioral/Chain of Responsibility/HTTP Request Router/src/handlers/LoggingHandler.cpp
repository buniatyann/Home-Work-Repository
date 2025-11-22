#include "../../include/handlers/LoggingHandler.hpp"
#include <iostream>

void LoggingHandler::doHandle(Request& req, Response& res) {
    std::cout << "[Logging] " << req.method << " " << req.path << "\n";
}