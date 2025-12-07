#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& instance();
    void log(const std::string& message);

private:
    Logger();
    std::ofstream logFile;
    std::mutex mtx;
};

#endif // LOGGER_HPP
