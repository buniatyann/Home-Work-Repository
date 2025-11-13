#ifndef RATELIMITINGDB_HPP
#define RATELIMITINGDB_HPP

#include "../interface/DatabaseDecorator.hpp"
#include <queue>
#include <chrono>
#include <mutex>

class RateLimitingDB : public DatabaseDecorator {
public:
    explicit RateLimitingDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;
private:
    std::queue<std::chrono::steady_clock::time_point> timestamps_;
    std::mutex mtx_;
};

#endif // RATELIMITINGDB_HPP