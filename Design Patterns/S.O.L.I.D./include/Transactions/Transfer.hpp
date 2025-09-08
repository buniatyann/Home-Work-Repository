#ifndef TRANSFER_HPP
#define TRANSFER_HPP

#include "Transaction.hpp"
#include <cstdint>

class Transfer : public Transaction {
public:
    Transfer(IAccount* fromAcc, IAccount* toAcc, uint64_t amount, ILogger* logger);
    void execute() override;
    std::string getDescription() const override;
    void rollback() override;
    std::string getType() const override;

private:
    IAccount* toAccount_;
};

#endif // TRANSFER_HPP