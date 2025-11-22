#include "../../include/internal/Handler.hpp"

IHandler* IHandler::setNext(std::unique_ptr<IHandler> handler) {
    next_ = std::move(handler);
    return next_.get();
}

void IHandler::handle(Request& req, Response& res) {
    doHandle(req, res);
    if (!res.handled && next_) {
        next_->handle(req, res);
    }
}