#ifndef STOCK_HPP
#define STOCK_HPP

#include "Observer.hpp"
#include <vector>
#include <string>
#include <mutex>
#include <memory>

class Stock {
public:
    Stock(const std::string& symbol, double price = 100.0);

    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);
    void notify() const;

    const std::string& getSymbol() const { return symbol_; }
    double getPrice() const { return price_; }
    void setPrice(double price);

private:
    std::vector<std::weak_ptr<Observer>> observers_;  // weak_ptr to avoid cycles
    std::string symbol_;
    
    double price_;
    mutable std::mutex mtx_;
};

#endif // STOCK_HPP