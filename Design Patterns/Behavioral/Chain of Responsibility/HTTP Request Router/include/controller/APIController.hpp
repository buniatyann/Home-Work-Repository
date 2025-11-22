#ifndef API_CONTROLLER_HPP
#define API_CONTROLLER_HPP

#include "../internal/Handler.hpp"
#include <iostream>

class APIController : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif // API_CONTROLLER_HPP