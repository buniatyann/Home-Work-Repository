#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Stock;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const Stock& stock) = 0;
};

#endif // OBSERVER_HPP