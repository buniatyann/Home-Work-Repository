#ifndef CONSERVATIVE_BIDDER_HPP
#define CONSERVATIVE_BIDDER_HPP

#include "../Observer.hpp"
#include <random>

class ConservativeBidder : public Observer {
public:
    ConservativeBidder(const std::string& name, Auction& auction, double maxBudget);
    void update(const Auction& auction, const Bid& newBid) override;
    std::string getName() const override { return name_; }

private:
    std::string name_;
    Auction& auction_;
    double maxBudget_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> delayDist_;
};

#endif // CONSERVATIVE_BIDDER_HPP