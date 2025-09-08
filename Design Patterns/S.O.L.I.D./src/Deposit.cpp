#include "../include/Transactions/Deposit.hpp"

Deposit::Deposit(IAccount* acc, uint64_t amount, ILogger* logger)
    : Transaction(acc, amount, logger) {}

void Deposit::execute() {
    if (!executed_) {
        account_->deposit(amount_);
        executed_ = true;
    }
}

std::string Deposit::getDescription() const {
    return "Deposit of " + std::to_string(amount_ / 100.0) + " to account " + account_->getAccountNumber();
}

void Deposit::rollback() {
    if (executed_) {
        account_->withdraw(amount_);
        executed_ = false;
        logger_->log("Rolled back deposit of " + std::to_string(amount_ / 100.0) + " from account " + account_->getAccountNumber());
    }
}

std::string Deposit::getType() const {
    return "Deposit";
}