#ifndef WITHDRAW_HPP
#define WITHDRAW_HPP

#include "Transaction.hpp"
#include <cstdint>

class Withdraw : public Transaction {
public:
    Withdraw(IAccount* acc, uint64_t amount, ILogger* logger);
    void execute() override;
    std::string getDescription() const override;
    void rollback() override;
    std::string getType() const override;
};


#endif // WITHDRAW_HPP