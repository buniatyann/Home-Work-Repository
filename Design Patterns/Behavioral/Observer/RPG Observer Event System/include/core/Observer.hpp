#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <memory>
#include <any>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const std::any& eventData, int eventType) = 0;
};

using ObserverPtr = std::shared_ptr<Observer>;
using ObserverWeakPtr = std::weak_ptr<Observer>;

#endif // OBSERVER_HPP