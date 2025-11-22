#include "../../include/handlers/AuthorizationHandler.hpp"
#include <iostream>

void AuthorizationHandler::doHandle(Request& req, Response& res) {
    std::cout << "[AuthZ] Checking permissions...\n";

    if (!req.isAuthenticated) {
        res.statusCode = 401;
        res.body = "Authentication required";
        res.handled = true;
        
        return;
    }

    if (req.path.find("/admin") != std::string::npos && req.userRole != "admin") {
        std::cout << "[AuthZ] Access denied – admin only\n";
        res.statusCode = 403;
        res.body = "Forbidden";
        res.handled = true;
    } 
    else {
        std::cout << "[AuthZ] Access granted\n";
    }
}