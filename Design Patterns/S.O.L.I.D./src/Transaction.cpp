#include "../include/Transactions/Transaction.hpp"

Transaction::Transaction(IAccount* acc, uint64_t amount, ILogger* logger)
    : amount_(amount), account_(acc), logger_(logger), executed_(false) {}

uint64_t Transaction::getAmount() const {
    return amount_;
}