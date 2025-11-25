#include "../include/bidders/ConservativeBidder.hpp"
#include <thread>
#include <chrono>
#include <iostream>

ConservativeBidder::ConservativeBidder(const std::string& name, Auction& auction, double maxBudget)
    : name_(name), auction_(auction), maxBudget_(maxBudget),
      gen_(std::random_device{}()), delayDist_(3000, 8000) {}

void ConservativeBidder::update(const Auction& auction, const Bid& newBid) {
    if (newBid.bidderName == name_) return;

    double current = this->auction_.getCurrentPrice();
    double myBid = current * 1.15;  // Only bid 15% higher

    if (myBid <= maxBudget_ && myBid > current) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayDist_(gen_)));
        if (auction_.isActive() && auction_.getCurrentPrice() < myBid) {
            auction_.placeBid(name_, myBid);
        }
    }
}