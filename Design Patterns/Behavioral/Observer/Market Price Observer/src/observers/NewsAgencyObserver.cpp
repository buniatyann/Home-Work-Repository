#include "../../include/observers/NewsAgencyObserver.hpp"
#include <iostream>

void NewsAgencyObserver::update(const Stock& stock) {
    std::cout << "[NEWS] BREAKING: " << stock.getSymbol()
              << " stock price changed to $" << stock.getPrice() << "!\n";
}