#include "../../include/observers/ChartObserver.hpp"
#include <iostream>

void ChartObserver::update(const Stock& stock) {
    std::cout << "[Chart] Updating graph for " << stock.getSymbol()
              << " → New price: $" << stock.getPrice() << "\n";
}