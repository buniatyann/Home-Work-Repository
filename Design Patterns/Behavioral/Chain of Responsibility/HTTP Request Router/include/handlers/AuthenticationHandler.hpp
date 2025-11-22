#ifndef AUTHENTICATION_HANDLER_HPP
#define AUTHENTICATION_HANDLER_HPP

#include "../internal/Handler.hpp"

class AuthenticationHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif