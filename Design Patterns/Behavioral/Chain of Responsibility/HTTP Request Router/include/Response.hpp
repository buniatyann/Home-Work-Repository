#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>

struct Response {
    int statusCode = 200;
    std::string body;
    bool handled = false;   // if true stop the chain
};

#endif