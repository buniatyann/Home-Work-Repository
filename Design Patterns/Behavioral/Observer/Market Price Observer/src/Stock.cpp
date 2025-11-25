#include "../include/Stock.hpp"
#include <algorithm>
#include <iostream>

Stock::Stock(const std::string& symbol, double price)
    : symbol_(symbol), price_(price) {}

void Stock::attach(std::shared_ptr<Observer> observer) {
    std::lock_guard<std::mutex> lock(mtx_);
    observers_.push_back(observer);
}

void Stock::detach(std::shared_ptr<Observer> observer) {
    std::lock_guard<std::mutex> lock(mtx_);
    observers_.erase(
        std::remove_if(observers_.begin(), observers_.end(),
            [&observer](const std::weak_ptr<Observer>& ptr) {
                return ptr.lock() == observer;
            }),
        observers_.end()
    );
}

void Stock::setPrice(double price) {
    {
        std::lock_guard<std::mutex> lock(mtx_);
        price_ = price;
    }
    
    notify();
}

void Stock::notify() const {
    std::vector<std::shared_ptr<Observer>> alive;

    {
        std::lock_guard<std::mutex> lock(mtx_);
        for (auto it = observers_.begin(); it != observers_.end();) {
            if (auto obs = it->lock()) {
                alive.push_back(obs);
                ++it;
            } 
            else {
                it = observers_.erase(it);
            }
        }
    }

    for (auto& obs : alive) {
        obs->update(*this);
    }
}
