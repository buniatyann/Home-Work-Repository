#ifndef AGGRESSIVE_BIDDER_HPP
#define AGGRESSIVE_BIDDER_HPP

#include "../Observer.hpp"
#include <random>

class AggressiveBidder : public Observer {
public:
    explicit AggressiveBidder(const std::string& name, Auction& auction, double maxBudget);
    void update(const Auction& auction, const Bid& newBid) override;
    std::string getName() const override { return name_; }

private:
    std::string name_;
    Auction& auction_;
    double maxBudget_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> delayDist_;
};

#endif