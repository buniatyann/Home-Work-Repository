#include "../../include/Interface/IChatbot.h"

void IChatbot::setContext(const std::string& key, const std::string& value) {
    manager_.setContext(key, value);
}

std::string IChatbot::getContext(const std::string& key) const {
    return manager_.getContext(key);
}

