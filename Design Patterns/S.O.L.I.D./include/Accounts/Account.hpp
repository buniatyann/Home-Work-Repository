#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "../Interfaces/IAccount.hpp"
#include "../Interfaces/ILogger.hpp"
#include <string>

class Account : public IAccount {
public:
    Account(const std::string& accountNumber, uint64_t initBalance, ILogger* logger);
    uint64_t getBalance() const override;
    std::string getAccountNumber() const override;
    void deposit(uint64_t amount) override;
    bool withdraw(uint64_t amount) override;
    virtual std::string getAccountType() const = 0;

protected:
    std::string accountNumber_;
    ILogger* logger_;
    uint64_t balance_;
};

#endif // ACCOUNT_HPP