#include "Logger.hpp"

Logger Logger::logger_;
std::mutex Logger::mtx_;

Logger &Logger::getInstance() {
    return logger_;
}

void Logger::log(const std::string &message) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << "[LOG]: " << message << std::endl;
}
