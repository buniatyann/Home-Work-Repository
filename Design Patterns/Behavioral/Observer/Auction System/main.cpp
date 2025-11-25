#include <iostream>
#include <thread>
#include <chrono>
#include "include/Auction.hpp"
#include "include/bidders/AggressiveBidder.hpp"
#include "include/bidders/ConservativeBidder.hpp"
#include "include/bidders/SniperBidder.hpp"

int main() {
    std::cout << R"(
    REAL-TIME AUCTION SYSTEM
    Observer Pattern - Live Bidding Battle!
    )" << std::endl;

    Auction auction("Vintage 1999 Pokémon Charizard Card (PSA 10)", 8000.0);

    auto alice   = std::make_shared<AggressiveBidder>("Alice (Aggressive)", auction, 12000);
    auto bob     = std::make_shared<AggressiveBidder>("Bob (Aggressive)", auction, 11000);
    auto carl    = std::make_shared<ConservativeBidder>("Carl (Conservative)", auction, 15000);
    auto diana   = std::make_shared<SniperBidder>("Diana (Sniper)", auction, 20000);
    auto eve     = std::make_shared<ConservativeBidder>("Eve (Conservative)", auction, 13000);

    auction.attach(alice);
    auction.attach(bob);
    auction.attach(carl);
    auction.attach(diana);
    auction.attach(eve);

    auction.start();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    auction.placeBid("Alice (Aggressive)", 8200);

    std::this_thread::sleep_for(std::chrono::seconds(30));
    auction.end();
    std::cout << "\nFinal price: $" << auction.getCurrentPrice() << "\n";
    if (auction.getHighestBid()) {
        std::cout << "Winner: " << auction.getHighestBid()->bidderName << "\n";
    }

    return 0;
}