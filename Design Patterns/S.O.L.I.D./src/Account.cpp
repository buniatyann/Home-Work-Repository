#include "../include/Account/Account.hpp"
#include <stdexcept>

Account::Account(const std::string& accountNumber, uint64_t initBalance, ILogger* logger)
    : accountNumber_(accountNumber), logger_(logger), balance_(initBalance) {
    logger_->log("Account " + accountNumber_ + " created with balance " + std::to_string(initBalance / 100.0));
}

uint64_t Account::getBalance() const {
    return balance_;
}

std::string Account::getAccountNumber() const {
    return accountNumber_;
}

void Account::deposit(uint64_t amount) {
    balance_ += amount;
    logger_->log("Deposited " + std::to_string(amount / 100.0) + " to account " + accountNumber_);
}

bool Account::withdraw(uint64_t amount) {
    if (amount > balance_) {
        logger_->log("Withdrawal failed: Insufficient funds in account " + accountNumber_);
        return false;
    }
 
    balance_ -= amount;
    logger_->log("Withdrew " + std::to_string(amount / 100.0) + " from account " + accountNumber_);
 
    return true;
}