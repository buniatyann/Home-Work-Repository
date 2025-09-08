#include "../include/Services/Logger.hpp"
#include <iostream>

Logger& Logger::getInstance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string& message) {
    std::cout << "[LOG]: " << message << std::endl;
}