#ifndef LOGGING_HANDLER_HPP
#define LOGGING_HANDLER_HPP

#include "../internal/Handler.hpp"

class LoggingHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif