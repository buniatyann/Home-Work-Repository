#include "../../include/utils/Logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    logFile.open("pipeline_log.txt", std::ios::out | std::ios::app);
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    logFile << std::ctime(&now_time) << ": " << message << std::endl;
}
