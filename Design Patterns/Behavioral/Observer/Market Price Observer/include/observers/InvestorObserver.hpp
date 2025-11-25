#ifndef INVESTOR_OBSERVER_HPP
#define INVESTOR_OBSERVER_HPP

#include "../Observer.hpp"

class InvestorObserver : public Observer, public std::enable_shared_from_this<InvestorObserver> {
public:
    explicit InvestorObserver(const std::string& name);
    void update(const Stock& stock) override;
    
private:
    std::string name_;
};

#endif