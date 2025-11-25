#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Bid.hpp"
class Auction;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const Auction& auction, const Bid& newBid) = 0;
    virtual std::string getName() const = 0;
};

#endif