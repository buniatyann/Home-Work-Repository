#include "../../include/bidders/AggressiveBidder.hpp"
#include <thread>
#include <chrono>

AggressiveBidder::AggressiveBidder(const std::string& name, Auction& auction, double maxBudget)
    : name_(name), auction_(auction), maxBudget_(maxBudget), gen_(std::random_device{}()),
      delayDist_(500, 2000) {}

void AggressiveBidder::update(const Auction& auction, const Bid& newBid) {
    if (newBid.bidderName == name_) return;

    double current = auction.getCurrentPrice();
    if (current + 10 <= maxBudget_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayDist_(gen_)));
        auction_.placeBid(name_, current + 10 + (std::rand() % 20));
    }
}