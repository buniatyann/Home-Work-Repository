#ifndef RATE_LIMIT_HANDLER_HPP
#define RATE_LIMIT_HANDLER_HPP

#include "../internal/Handler.hpp"

class RateLimitHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif