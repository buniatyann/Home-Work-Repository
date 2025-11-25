#ifndef BID_HPP
#define BID_HPP

#include <string>

struct Bid {
    std::string bidderName;
    double amount;
    Bid(const std::string& name, double amt) : bidderName(name), amount(amt) {}
};

#endif