#include "../../include/handlers/CorsHandler.hpp"
#include <iostream>

void CorsHandler::doHandle(Request& req, Response& res) {
    std::cout << "[CORS] Adding Access-Control-Allow-Origin: *\n";
}