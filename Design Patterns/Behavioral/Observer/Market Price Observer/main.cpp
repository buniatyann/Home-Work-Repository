#include <iostream>
#include <memory>
#include <thread>
#include "Stock.hpp"
#include "include/observers/RichObserver.hpp"
#include "include/observers/InvestorObserver.hpp"
#include "include/observers/NewsAgencyObserver.hpp"
#include "include/observers/ChartObserver.hpp"
#include "include/StockMarketService.hpp"

int main() {
    std::cout << "=== Stock Market Observer Pattern Demo ===\n\n";

    Stock apple("AAPL", 170.0);
    Stock tesla("TSLA", 250.0);
    Stock google("GOOGL", 2800.0);

    auto warren  = std::make_shared<RichObserver>("Warren Buffett");
    auto elon    = std::make_shared<InvestorObserver>("Elon Musk");
    auto cnbc    = std::make_shared<NewsAgencyObserver>();
    auto chart   = std::make_shared<ChartObserver>();

    apple.attach(warren);
    apple.attach(elon);
    apple.attach(cnbc);
    apple.attach(chart);

    tesla.attach(elon);
    tesla.attach(chart);

    google.attach(warren);
    google.attach(cnbc);

    std::vector<Stock*> allStocks = {&apple, &tesla, &google};

    StockMarketService market(allStocks);
    std::thread marketThread(&StockMarketService::simulateMarket, &market);

    marketThread.join();

    std::cout << "\n=== Market closed. Final prices ===\n";
    std::cout << apple.getSymbol() << ": $" << apple.getPrice() << "\n";
    std::cout << tesla.getSymbol() << ": $" << tesla.getPrice() << "\n";
    std::cout << google.getSymbol() << ": $" << google.getPrice() << "\n";

    return 0;
}