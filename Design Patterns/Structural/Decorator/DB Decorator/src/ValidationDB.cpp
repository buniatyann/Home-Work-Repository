#include "../include/decorators/ValidationDB.hpp"
#include <algorithm>

ValidationDB::ValidationDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

bool ValidationDB::safe(const std::string& q) const {
    std::string upper = q;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    for (const auto& bad : forbidden_) {
        if (upper.find(bad) != std::string::npos) {
            return false;
        }
    }

    return true;
}

std::string ValidationDB::execute(const std::string& q,
                                  const std::unordered_map<std::string, std::string>& p) {
    if (!safe(q)) {
        return "[VALIDATION] Forbidden keyword detected";
    }    
    
    return DatabaseDecorator::execute(q, p);
}