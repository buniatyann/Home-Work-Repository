#ifndef CORS_HANDLER_HPP
#define CORS_HANDLER_HPP

#include "../internal/Handler.hpp"

class CorsHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif