#include "../include/decorators/LoggingDB.hpp"
#include "../include/settings/Settings.hpp"
#include <fstream>
#include <chrono>

LoggingDB::LoggingDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

void LoggingDB::writeLog(const std::string& msg) {
    std::ofstream f(settings::LOG_FILE, std::ios::app);
    if (f) {
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        f << std::ctime(&t) << msg << "\n";
    }
}

std::string LoggingDB::execute(const std::string& q,
                               const std::unordered_map<std::string, std::string>& p) {
    writeLog("EXEC: " + q);
    std::string res = DatabaseDecorator::execute(q, p);
    writeLog("RESULT: " + res);

    return res;
}