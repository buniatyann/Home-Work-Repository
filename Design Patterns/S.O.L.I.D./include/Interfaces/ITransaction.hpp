#ifndef ITRANSACTION_HPP
#define ITRANSACTION_HPP

#include <string>

class ITransaction {
public:
    virtual ~ITransaction() = default;
    virtual void execute() = 0;
    virtual std::string getDescription() const = 0;
    virtual void rollback() = 0;
    virtual uint64_t getAmount() const = 0;
    virtual std::string getType() const = 0;
};

#endif // ITRANSACTION_HPP