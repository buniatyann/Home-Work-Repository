#include "../include/Transactions/Withdraw.hpp"

Withdraw::Withdraw(IAccount* acc, uint64_t amount, ILogger* logger)
    : Transaction(acc, amount, logger) {}

void Withdraw::execute() {
    if (!executed_) {
        if (account_->withdraw(amount_)) {
            executed_ = true;
        } 
        else {
            logger_->log("Withdrawal transaction failed for account " + account_->getAccountNumber());
        }
    }
}

std::string Withdraw::getDescription() const {
    return "Withdrawal of " + std::to_string(amount_ / 100.0) + " from account " + account_->getAccountNumber();
}

void Withdraw::rollback() {
    if (executed_) {
        account_->deposit(amount_);
        executed_ = false;
        logger_->log("Rolled back withdrawal of " + std::to_string(amount_ / 100.0) + " from account " + account_->getAccountNumber());
    }
}

std::string Withdraw::getType() const {
    return "Withdraw";
}