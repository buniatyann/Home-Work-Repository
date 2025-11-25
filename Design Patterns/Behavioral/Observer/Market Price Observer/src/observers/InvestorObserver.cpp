#include "../../include/observers/InvestorObserver.hpp"
#include <iostream>

InvestorObserver::InvestorObserver(const std::string& name) : name_(name) {}

void InvestorObserver::update(const Stock& stock) {
    if (stock.getPrice() > 300) {
        std::cout << "[Investor] " << name_ << " SELLING " << stock.getSymbol() << " at $" << stock.getPrice() << "!\n";
    } 
    else if (stock.getPrice() < 150) {
        std::cout << "[Investor] " << name_ << " BUYING " << stock.getSymbol() << " at $" << stock.getPrice() << "!\n";
    }
}