#ifndef AUTHORIZATION_HANDLER_HPP
#define AUTHORIZATION_HANDLER_HPP

#include "../internal/Handler.hpp"

class AuthorizationHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif