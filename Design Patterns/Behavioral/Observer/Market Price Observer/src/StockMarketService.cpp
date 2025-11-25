#include "../include/StockMarketService.hpp"
#include <random>
#include <thread>
#include <chrono>
#include <iostream>

StockMarketService::StockMarketService(std::vector<Stock*>& stocks) : stocks_(stocks) {}

void StockMarketService::simulateMarket() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> priceDist(100.0, 600.0);
    std::uniform_real_distribution<> delayDist(1.0, 4.0);

    for (int i = 0; i < 15; ++i) {
        for (auto* stock : stocks_) {
            double newPrice = priceDist(gen);
            std::cout << "\n[Market] Updating " << stock->getSymbol()
                      << " → New price: $" << newPrice << "\n";
            stock->setPrice(newPrice);
        }
       
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}