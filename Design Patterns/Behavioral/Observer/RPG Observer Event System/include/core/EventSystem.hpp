#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include "Subject.hpp"

class EventSystem {
    // some functionality like loading, etc.
public:
    static EventSystem& getInstance() {
        static EventSystem events;
        return events;
    } 

private:
    EventSystem() = default;
};

#endif // EVENT_SYSTEM_HPP