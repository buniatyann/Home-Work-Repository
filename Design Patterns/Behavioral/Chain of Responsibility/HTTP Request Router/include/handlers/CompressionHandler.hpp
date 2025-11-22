#ifndef COMPRESSION_HANDLER_HPP
#define COMPRESSION_HANDLER_HPP

#include "../internal/Handler.hpp"

class CompressionHandler : public Handler {
protected:
    void doHandle(Request& req, Response& res) override;
};

#endif