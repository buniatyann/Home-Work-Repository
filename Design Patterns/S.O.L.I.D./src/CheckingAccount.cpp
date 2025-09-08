#include "../include/Accounts/CheckingAccount.hpp"

CheckingAccount::CheckingAccount(const std::string& accNum, uint64_t initialBalance, uint64_t overdraft, ILogger* logger)
    : Account(accNum, initialBalance, logger.get()), overdraftLimit_(overdraft) {
    logger_->log("CheckingAccount " + accNum + " created with overdraft limit " + std::to_string(overdraft / 100.0));
}

bool CheckingAccount::withdraw(uint64_t amount) {
    if (amount > (balance_ + overdraftLimit_)) {
        logger_->log("Withdrawal failed: Exceeds overdraft limit for account " + accountNumber_);
        return false;
    }

    balance_ -= amount;
    logger_->log("Withdrew " + std::to_string(amount / 100.0) + " from account " + accountNumber_);
    
    return true;
}

std::string CheckingAccount::getAccountType() const {
    return "Checking";
}