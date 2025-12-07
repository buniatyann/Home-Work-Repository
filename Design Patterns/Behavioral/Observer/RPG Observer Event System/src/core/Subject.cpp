#include "../../include/core/Subject.hpp"
#include <iostream>

void Subject::addObserver(ObserverWeakPtr observer) {
    observers_.push_back(observer);
}

void Subject::removeObserver(ObserverPtr observer) {
    observers_.erase(
        std::remove_if(observers_.begin(), observers_.end(),
            [&observer](const ObserverWeakPtr& weak) {
                auto locked = weak.lock();
                return !locked || locked == observer;
            }),
        observers_.end());
}

void Subject::notify(const std::any& eventData, int eventType) {
    for (auto it = observers_.begin(); it != observers_.end(); ) {
        if (auto observer = it->lock()) {
            observer->onNotify(eventData, eventType);
            ++it;
        } 
        else {
            it = observers_.erase(it);  
        }
    }
}