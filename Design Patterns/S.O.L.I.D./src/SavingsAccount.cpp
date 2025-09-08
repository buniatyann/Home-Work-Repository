#include "../include/Accounts/SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const std::string& accNum, uint64_t initBalance, double rate, ILogger* logger)
    : Account(accNum, initBalance, logger), interestRate_(rate) {
    logger_->log("SavingsAccount " + accNum + " created with interest rate " + std::to_string(rate));
}

std::string SavingsAccount::getAccountType() const {
    return "Savings";
}

void SavingsAccount::applyInterest() {
    uint64_t interest = static_cast<uint64_t>(balance_ * interestRate_);
    deposit(interest);
    
    logger_->log("Applied interest of " + std::to_string(interest / 100.0) + " to account " + accountNumber_);
}