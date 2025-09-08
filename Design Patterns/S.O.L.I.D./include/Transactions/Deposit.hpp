#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include "Transaction.hpp"

class Deposit : public Transaction {
public:
    Deposit(IAccount* acc, uint64_t amount, ILogger* logger);
    void execute() override;
    std::string getDescription() const override;
    void rollback() override;
    std::string getType() const override;
};

#endif // DEPOSIT_HPP