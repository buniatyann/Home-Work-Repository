#include "../include/Transactions/Transfer.hpp"

Transfer::Transfer(IAccount* fromAcc, IAccount* toAcc, uint64_t amount, ILogger* logger)
    : Transaction(fromAcc, amount, logger), toAccount_(toAcc) {}

void Transfer::execute() {
    if (!executed_) {
        if (account_->withdraw(amount_)) {
            toAccount_->deposit(amount_);
            executed_ = true;
            logger_->log("Transferred " + std::to_string(amount_ / 100.0) + " from account " +
                         account_->getAccountNumber() + " to account " + toAccount_->getAccountNumber());
        } 
        else {
            logger_->log("Transfer failed from account " + account_->getAccountNumber());
        }
    }
}

std::string Transfer::getDescription() const {
    return "Transfer of " + std::to_string(amount_ / 100.0) + " from account " +
           account_->getAccountNumber() + " to account " + toAccount_->getAccountNumber();
}

void Transfer::rollback() {
    if (executed_) {
        if (toAccount_->withdraw(amount_)) {
            account_->deposit(amount_);
            executed_ = false;
            logger_->log("Rolled back transfer of " + std::to_string(amount_ / 100.0) +
                         " from account " + account_->getAccountNumber() + " to account " + toAccount_->getAccountNumber());
        }
    }
}

std::string Transfer::getType() const {
    return "Transfer";
}