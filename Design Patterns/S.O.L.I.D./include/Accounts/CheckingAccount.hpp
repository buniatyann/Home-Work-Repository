#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP

#include "Account.hpp"
#include <memory>

class CheckingAccount : public Account {
public:
    CheckingAccount(const std::string& accNum, uint64_t initialBalance, uint64_t overdraft, ILogger* logger);
    bool withdraw(uint64_t amount) override;
    std::string getAccountType() const override;

private:
    uint64_t overdraftLimit_;
};

#endif // CHECKINGACCOUNT_HPP