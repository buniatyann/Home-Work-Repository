#ifndef SAVINGSACCOUNT_HPP
#define SAVINGSACCOUNT_HPP

#include "Account.hpp"

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& accNum, uint64_t initBalance, double rate, ILogger* logger);
    std::string getAccountType() const override;
    void applyInterest();

private:
    double interestRate_;
};

#endif // SAVINGSACCOUNT_HPP