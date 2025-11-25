#ifndef AUCTION_HPP
#define AUCTION_HPP

#include "Observer.hpp"
#include "Bid.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <string>
#include <optional>

class Auction {
public:
    Auction(const std::string& item, double startingPrice, int durationSeconds = 30);

    void attach(std::shared_ptr<Observer> bidder);
    void detach(std::shared_ptr<Observer> bidder);
    void notify(const Bid& bid) const;

    void placeBid(const std::string& bidderName, double amount);
    void start();
    void end();

    const std::string& getItem() const { return item_; }
    double getCurrentPrice() const { return currentPrice_; }
    const Bid* getHighestBid() const { return highestBid_ ? &*highestBid_ : nullptr; }
    bool isActive() const { return active_; }

private:
    std::string item_;
    double startingPrice_;
    double currentPrice_;
    std::optional<Bid> highestBid_;
    bool active_ = false;

    mutable std::mutex mtx_;
    std::vector<std::weak_ptr<Observer>> bidders_;
};

#endif