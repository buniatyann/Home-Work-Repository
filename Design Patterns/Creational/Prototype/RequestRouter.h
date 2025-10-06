#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "IChatbot.h"
#include <memory>
#include <string>

class RequestRouter {
private:
    std::unique_ptr<IChatbot> weatherBotPrototype_;
    std::unique_ptr<IChatbot> bookingBotPrototype_;
    ContextManager contextManager_;

public:
    RequestRouter(std::unique_ptr<IChatbot> weatherBot, std::unique_ptr<IChatbot> bookingBot);
    std::string routeRequest(const std::string& userId, const std::string& request);
};

#endif // REQUESTROUTER_H