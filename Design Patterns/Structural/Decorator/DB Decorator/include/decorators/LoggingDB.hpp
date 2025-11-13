#ifndef LOGGINGDB_HPP
#define LOGGINGDB_HPP

#include "../interface/DatabaseDecorator.hpp"

class LoggingDB : public DatabaseDecorator {
public:
    explicit LoggingDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;
private:
    void writeLog(const std::string& msg);
};

#endif // LOGGINGDB_HPP