#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "ParseResult.hpp"
#include <string> 
#include <memory>

class Handler {
public:
    virtual ~Handler() = default;
    std::unique_ptr<Handler> setNext(std::unique_ptr<Handler> handler) {
       next_ = std::move(handler);
       return std::make_unique<Handler>(next_); 
    }

    virtual ParseResult handle(const std::string& input) {
        ParseResult res = doParse(input);
        if (res.success || !next_) {
            return res;
        }

        return next_->handle(input);
    }

protected:
    std::unique_ptr<Handler> next_;

    virtual ParseResult doParse(const std::string& input) = 0;
};

#endif // HANDLER_HPP