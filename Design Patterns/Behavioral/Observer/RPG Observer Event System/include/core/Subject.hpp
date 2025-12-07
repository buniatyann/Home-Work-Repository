#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>
#include <algorithm>
#include <memory>

class Subject {
public:
    void addObserver(ObserverWeakPtr observer);
    void removeObserver(ObserverPtr observer);
    void notify(const std::any& eventData, int eventType);

private:
    std::vector<ObserverWeakPtr> observers_;
};

#endif // SUBJECT_HPP