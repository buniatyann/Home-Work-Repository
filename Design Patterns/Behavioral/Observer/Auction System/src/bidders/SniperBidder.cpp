#include "../include/bidders/SniperBidder.hpp"
#include <thread>
#include <chrono>
#include <iostream>

SniperBidder::SniperBidder(const std::string& name, Auction& auction, double maxBudget)
    : name_(name), auction_(auction), maxBudget_(maxBudget) {
    // Sniper waits until last moment
    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(25));  
        if (auction_.isActive() && !hasBid_.load()) {
            double finalBid = auction_.getCurrentPrice() + 100;  
            if (finalBid <= maxBudget_) {
                auction_.placeBid(name_, finalBid);
                hasBid_.store(true);
            }
        }
    }).detach();
}

void SniperBidder::update(const Auction& auction, const Bid& newBid) {
    if (newBid.bidderName != name_) {
        std::cout << "[Sniper] " << name_ << " is waiting... watching " << newBid.bidderName << " bid $" << newBid.amount << "\n";
    }
}