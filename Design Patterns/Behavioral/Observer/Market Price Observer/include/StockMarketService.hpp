#ifndef STOCK_MARKET_SERVICE_HPP
#define STOCK_MARKET_SERVICE_HPP

#include "Stock.hpp"
#include <vector>

class StockMarketService {
public:
    explicit StockMarketService(std::vector<Stock*>& stocks);
    void simulateMarket();

private:
    std::vector<Stock*> stocks_;
};

#endif // STOCK_MARKET_SERVICE_HPP