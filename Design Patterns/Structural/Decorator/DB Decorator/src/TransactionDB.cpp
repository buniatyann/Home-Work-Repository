#include "../include/decorators/TransactionDB.hpp"
#include <algorithm>

TransactionDB::TransactionDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

bool TransactionDB::isCmd(const std::string& q, const std::string& cmd) {
    std::string upper = q;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    
    return upper.find(cmd) != std::string::npos;
}

std::string TransactionDB::execute(const std::string& q,
                                   const std::unordered_map<std::string, std::string>& p) {
    if (isCmd(q, "BEGIN")) {
        if (in_transaction_) {
            return "[ERROR] Transaction already active";
        }
        
        in_transaction_ = true;
        buffer_.clear();
        
        return "[TX] BEGIN";
    }
    if (isCmd(q, "COMMIT")) {
        if (!in_transaction_) {
            return "[ERROR] No active transaction";
        }

        std::string out = "[TX] COMMITTING\n";
        for (const auto& [sql, prm] : buffer_) {
            out += DatabaseDecorator::execute(sql, prm) + "\n";
        }
        
        out += "[TX] COMMITTED";
        in_transaction_ = false;
        buffer_.clear();
        
        return out;
    }
    if (isCmd(q, "ROLLBACK")) {
        if (!in_transaction_) {
            return "[ERROR] No active transaction";
        }

        in_transaction_ = false;
        buffer_.clear();
        
        return "[TX] ROLLBACK";
    }
    if (in_transaction_) {
        buffer_.emplace_back(q, p);
        return "[TX] buffered";
    }

    return DatabaseDecorator::execute(q, p);
}