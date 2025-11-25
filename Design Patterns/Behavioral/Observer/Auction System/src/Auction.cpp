#include "../include/Auction.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

Auction::Auction(const std::string& item, double startingPrice, int durationSeconds)
    : item_(item), startingPrice_(startingPrice), currentPrice_(startingPrice) {}

void Auction::attach(std::shared_ptr<Observer> bidder) {
    std::lock_guard<std::mutex> lock(mtx_);
    bidders_.push_back(bidder);
}

void Auction::detach(std::shared_ptr<Observer> bidder) {
    std::lock_guard<std::mutex> lock(mtx_);
    bidders_.erase(
        std::remove_if(bidders_.begin(), bidders_.end(),
            [&bidder](const std::weak_ptr<Observer>& ptr) { return ptr.lock() == bidder; }),
        bidders_.end());
}

void Auction::notify(const Bid& bid) const {
    std::lock_guard<std::mutex> lock(mtx_);
    for (auto it = bidders_.begin(); it != bidders_.end(); ) {
        if (auto observer = it->lock()) {
            observer->update(*this, bid);
            ++it;
        } 
        else {
            it = bidders_.erase(it);
        }
    }
}

void Auction::placeBid(const std::string& bidderName, double amount) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!active_) {
        std::cout << "Auction is not active!\n";
        return;
    }

    if (amount <= currentPrice_) {
        std::cout << bidderName << " bid too low! Current: $" << currentPrice_ << "\n";
        return;
    }

    currentPrice_ = amount;
    highestBid_ = Bid(bidderName, amount);

    std::cout << "\nNEW BID! " << bidderName << " → $" << amount << "\n";
    notify(*highestBid_);
}

void Auction::start() {
    active_ = true;
    std::cout << "AUCTION STARTED: \"" << item_ << "\" | Starting at $" << startingPrice_ << "\n";
    std::cout << "Bidding begins now! 30 seconds...\n\n";
}

void Auction::end() {
    active_ = false;
    std::cout << "\nTIME'S UP! AUCTION ENDED!\n";
    if (highestBid_) {
        std::cout << "WINNER: " << highestBid_->bidderName
                  << " with $" << highestBid_->amount << "!\n";
    } 
    else {
        std::cout << "No bids. Item unsold.\n";
    }
}