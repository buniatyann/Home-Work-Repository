#include "../../include/handlers/AuthenticationHandler.hpp"
#include <iostream>

void AuthenticationHandler::doHandle(Request& req, Response& res) {
    std::cout << "[Auth] Checking token...\n";
    auto authIt = req.headers.find("Authorization");
    if (authIt != req.headers.end() && authIt->second == "Bearer valid-token-123") {
        req.isAuthenticated = true;
        req.userId = 777;
        req.userRole = "admin";
        std::cout << "[Auth] Authenticated as admin (ID=777)\n";
    } 
    else {
        std::cout << "[Auth] Invalid or missing token\n";
        res.statusCode = 401;
        res.body = "Unauthorized";
        res.handled = true;
    }
}