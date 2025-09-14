#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <thread>

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message); 
    
private:
    Logger()=default;
    Logger(const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;
    Logger(Logger&&)=delete;
    Logger& operator=(Logger&&)=delete;

    static Logger logger_;
    static std::mutex mtx_;
};

#endif 