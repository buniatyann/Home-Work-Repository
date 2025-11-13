#ifndef TRANSACTIONDB_HPP
#define TRANSACTIONDB_HPP

#include "../interface/DatabaseDecorator.hpp"
#include <vector>

class TransactionDB : public DatabaseDecorator {
public:
    explicit TransactionDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;
private:
    bool in_transaction_ = false;
    std::vector<std::pair<std::string,
                         std::unordered_map<std::string, std::string>>> buffer_;
    bool isCmd(const std::string& q, const std::string& cmd);
};

#endif // TRANSACTIONDB_HPP