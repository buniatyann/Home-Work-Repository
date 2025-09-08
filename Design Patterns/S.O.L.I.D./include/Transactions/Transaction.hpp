#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "../Interfaces/IAccount.hpp"
#include "../Interfaces/ILogger.hpp"
#include "../Interfaces/ITransaction.hpp"
#include <string>
#include <cstdint>

class Transaction : public ITransaction {
public:
    Transaction(IAccount* acc, uint64_t amount, ILogger* logger);
    uint64_t getAmount() const override;
    virtual void execute() override = 0;
    virtual std::string getDescription() const override = 0;
    virtual void rollback() override = 0;
    virtual std::string getType() const override = 0;

protected:
    uint64_t amount_;
    IAccount* account_;
    ILogger* logger_;
    bool executed_;
};

#endif // TRANSACTION_HPP