#include "Logger.hpp"

std::mutex Logger::mtx_;

Logger &Logger::getInstance() {
    static Logger logger = Logger();
    return logger;
}

void Logger::log(const std::string &message) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << "[LOG]: " << message << std::endl;
}
