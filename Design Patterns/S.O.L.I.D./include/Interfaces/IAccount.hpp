#ifndef IACCOUNT_HPP
#define IACCOUNT_HPP

#include <string>
#include <stdexcept>

class IAccount {
public:
    virtual ~IAccount() = default;
    virtual uint64_t getBalance() const = 0;
    virtual void deposit(uint64_t amount) = 0;
    virtual bool withdraw(uint64_t amount) = 0;
    virtual std::string getAccountType() const = 0;
    virtual std::string getAccountNumber() const = 0;
};

#endif // IACCOUNT_HPP