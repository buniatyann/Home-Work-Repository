#ifndef SNIPER_BIDDER_HPP
#define SNIPER_BIDDER_HPP

#include "../Observer.hpp"
#include <atomic>

class SniperBidder : public Observer {
public:
    SniperBidder(const std::string& name, Auction& auction, double maxBudget);
    void update(const Auction& auction, const Bid& newBid) override;
    std::string getName() const override { return name_; }

private:
    std::string name_;
    Auction& auction_;
    double maxBudget_;
    std::atomic<bool> hasBid_{false};
};

#endif // SNIPER_BIDDER_HPP