#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <unordered_map>

struct Request {
    std::string method;
    std::string path;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> queryParams;

    // demo purposes
    std::string userRole = "guest";     // "admin", "user", "guest"
    bool isAuthenticated = false;
    int userId = -1;
};

#endif