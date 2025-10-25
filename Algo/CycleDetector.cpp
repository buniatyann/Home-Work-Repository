#include "List/Interface/IList.hpp"

template <typename T>
void concatenate(IList<T>& first, IList<T>& second) {
    first.backNode()->next() = second.frontNode();
    first.backNode() = second.backNode();
}


template <typename T>
bool hasCycle(IList<T>& list) {
    auto fast = list.frontNode();
    auto slow = list.frontNode();
    while (fast->next() && fast->next()->next()) {
        fast = fast->next()->next();
        slow = slow->next();
        if (fast == slow) {
            return true;
        }
    }

    return false;
}

template <typename T>
std::size_t cycleLength(IList<T>& list) {
    auto fast = list.frontNode();
    auto slow = list.frontNode();

    while (fast && fast->next() && fast->next()->next()) {
        fast = fast->next()->next();
        slow = slow->next();

        if (fast == slow) { // Cycle detected
            std::size_t length = 1; // Start counting from the meeting point
            auto cycle_node = slow->next();
            while (cycle_node != slow) {
                cycle_node = cycle_node->next();
                ++length;
            }

            return length;
        }
    }

    return 0; // No cycle
}
