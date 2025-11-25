#ifndef NEWS_AGENCY_OBSERVER_HPP
#define NEWS_AGENCY_OBSERVER_HPP

#include "../Observer.hpp"

class NewsAgencyObserver : public Observer {
public:
    void update(const Stock& stock) override;
};

#endif // NEWS_AGENCY_OBSERVER_HPP