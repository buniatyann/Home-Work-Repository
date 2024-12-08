#ifndef OBSERVER_H
#define OBSERVER_H

class Observer{
public:
    Observer() = default;
    virtual void notify() = 0;
};

#endif // OBSERVER_H