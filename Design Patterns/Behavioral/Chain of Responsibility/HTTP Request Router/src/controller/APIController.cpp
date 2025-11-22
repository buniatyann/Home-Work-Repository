#include "../../include/controller/APIController.hpp"
#include <iostream>
#include <sstream>

void APIController::doHandle(Request& req, Response& res) {
    std::cout << "[API] Processing business logic...\n";
    std::ostringstream json;
    json << R"({"message":"Welcome to the API!","userId":)" << req.userId
         << R"(,"role":")" << req.userRole << "\"}";

    res.body = json.str();
    res.handled = true;
}