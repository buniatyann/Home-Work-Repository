#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>
#include "LogLevel.hpp"

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(LogLevel level, const std::string& message) = 0;
};

#endif // ILOGGER_HPP