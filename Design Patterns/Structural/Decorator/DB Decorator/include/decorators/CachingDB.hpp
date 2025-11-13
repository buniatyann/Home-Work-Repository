#ifndef CACHINGDB_HPP
#define CACHINGDB_HPP

#include "../interface/DatabaseDecorator.hpp"
#include <unordered_map>

class CachingDB : public DatabaseDecorator {
public:
    explicit CachingDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;

private:
    std::unordered_map<std::string, std::string> cache_;
    std::string makeKey(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p);
};

#endif // CACHINGDB_HPP