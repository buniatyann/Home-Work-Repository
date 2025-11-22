#ifndef IHANDLER_HPP
#define IHANDLER_HPP

#include "Request.hpp"
#include "Response.hpp"
#include <memory>

class Handler {
public:
    virtual ~Handler() = default;

    Handler* setNext(std::unique_ptr<Handler> handler);
    void handle(Request& req, Response& res);

protected:
    std::unique_ptr<Handler> next_;
    virtual void doHandle(Request& req, Response& res) = 0;
};

#endif // IHANDLER_HPP