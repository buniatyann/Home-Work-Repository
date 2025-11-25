#ifndef CHART_OBSERVER_HPP
#define CHART_OBSERVER_HPP

#include "../Observer.hpp"

class ChartObserver : public Observer {
public:
    void update(const Stock& stock) override;
};

#endif // CHART_OBSERVER_HPP