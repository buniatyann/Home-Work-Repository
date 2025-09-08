#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../Interfaces/ILogger.hpp"
#include <string>

class Logger : public ILogger {
public:
    static Logger& getInstance();
    void log(const std::string& message) override;

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_HPP