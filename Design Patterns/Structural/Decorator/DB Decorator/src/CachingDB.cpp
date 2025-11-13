#include "../include/decorators/CachingDB.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

CachingDB::CachingDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

std::string CachingDB::makeKey(const std::string& q,
                               const std::unordered_map<std::string, std::string>& p) {
    std::ostringstream oss;
    oss << q;
    std::vector<std::string> keys;
    for (const auto& kv : p) { 
        keys.push_back(kv.first);
    }
    
    std::sort(keys.begin(), keys.end());
    for (const auto& k : keys) {
        oss << "|" << k << "=" << p.at(k);
    }
    
    return oss.str();
}

std::string CachingDB::execute(const std::string& q,
                               const std::unordered_map<std::string, std::string>& p) {
    std::string key = makeKey(q, p);
    if (auto it = cache_.find(key); it != cache_.end()) {
        std::cout << "[Cache] HIT  " << key << "\n";
        return it->second;
    }

    std::cout << "[Cache] MISS " << key << "\n";
    std::string res = DatabaseDecorator::execute(q, p);
    cache_[key] = res;
    
    return res;
}