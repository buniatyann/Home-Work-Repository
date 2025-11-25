#include "../../include/observers/RichObserver.hpp"
#include <iostream>

RichObserver::RichObserver(const std::string& name) : name_(name) {}

void RichObserver::update(const Stock& stock) {
    std::cout << "[Rich] " << name_ << " notified: "
              << stock.getSymbol() << " = $" << stock.getPrice() << "\n";
}