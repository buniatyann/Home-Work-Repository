#include "../include/decorators/RateLimitingDB.hpp"
#include "../include/settings/Settings.hpp"

RateLimitingDB::RateLimitingDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

std::string RateLimitingDB::execute(const std::string& q,
                                   const std::unordered_map<std::string, std::string>& p) {
    std::lock_guard<std::mutex> lk(mtx_);
    auto now = std::chrono::steady_clock::now();
    while (!timestamps_.empty()) {
        auto age = std::chrono::duration_cast<std::chrono::seconds>(now - timestamps_.front()).count();
        if (age > settings::TIME_WINDOW_SECONDS) {
            timestamps_.pop();
        }
        else {
            break;
        }
    }

    if (timestamps_.size() >= settings::RATE_LIMIT) {
        return "[ERROR] Rate limit exceeded (10 req / 60 s)";
    }

    timestamps_.push(now);
    return DatabaseDecorator::execute(q, p);
}