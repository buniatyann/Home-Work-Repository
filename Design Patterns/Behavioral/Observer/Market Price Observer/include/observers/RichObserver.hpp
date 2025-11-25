#ifndef RICH_OBSERVER_HPP
#define RICH_OBSERVER_HPP

#include "../Observer.hpp"
#include <string>

class RichObserver : public Observer {
public:
    explicit RichObserver(const std::string& name);
    void update(const Stock& stock) override;

private:
    std::string name_;
};

#endif