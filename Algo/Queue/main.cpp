#include "Array Based/Queue.hpp"
// #include "List Based/Queue.hpp"
#include <iostream>
#include <cassert>
#include <string>

int main() {
    Queue<int> q1;
    assert(q1.empty() && "Queue should be empty initially");
    assert(q1.size() == 0 && "Size should be 0 initially");

    q1.enqueue(1);
    q1.emplace(2);
    q1.enqueue(3);
    assert(q1.size() == 3 && "Size should be 3 after adding elements");
    assert(q1.front() == 1 && "Front should be 1");
    assert(q1.back() == 3 && "Back should be 3");

    q1.dequeue();
    assert(q1.size() == 2 && "Size should be 2 after dequeue");
    assert(q1.front() == 2 && "Front should be 2 after dequeue");
    assert(q1.back() == 3 && "Back should be 3 after dequeue");

    Queue<int> q2(q1);
    assert(q2.size() == 2 && "Copy constructor: size should be 2");
    assert(q2.front() == 2 && "Copy constructor: front should be 2");
    assert(q2.back() == 3 && "Copy constructor: back should be 3");
    q2.enqueue(4);
    assert(q2.size() == 3 && "Copy should be independent");
    assert(q1.size() == 2 && "Original queue should be unchanged");

    Queue<int> q3;
    q3 = q1;
    assert(q3.size() == 2 && "Copy assignment: size should be 2");
    assert(q3.front() == 2 && "Copy assignment: front should be 2");
    assert(q3.back() == 3 && "Copy assignment: back should be 3");
    q3.enqueue(5);
    assert(q3.size() == 3 && "Copy assignment should be independent");
    assert(q1.size() == 2 && "Original queue should be unchanged");

    Queue<int> q4(std::move(q1));
    assert(q4.size() == 2 && "Move constructor: size should be 2");
    assert(q4.front() == 2 && "Move constructor: front should be 2");
    assert(q4.back() == 3 && "Move constructor: back should be 3");
    assert(q1.empty() && "Moved-from queue should be empty");

    Queue<int> q5;
    q5 = std::move(q4);
    assert(q5.size() == 2 && "Move assignment: size should be 2");
    assert(q5.front() == 2 && "Move assignment: front should be 2");
    assert(q5.back() == 3 && "Move assignment: back should be 3");
    assert(q4.empty() && "Moved-from queue should be empty");

    Queue<std::string> q6;
    q6.enqueue("apple");
    q6.enqueue("banana");
    q6.enqueue("cherry");
    q6.dequeue();
    q6.enqueue("date");
    assert(q6.size() == 3 && "Size should be 3");
    assert(q6.front() == "banana" && "Front should be banana");
    assert(q6.back() == "date" && "Back should be date");

    try {
        Queue<int> q7;
        q7.dequeue();
        assert(false && "Dequeue on empty queue should throw");
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Dequeue from empty queue");
    }

    try {
        Queue<int> q8;
        q8.front();
        assert(false && "Front on empty queue should throw");
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Front of empty queue");
    }

    try {
        Queue<int> q9;
        q9.back();
        assert(false && "Back on empty queue should throw");
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Back of empty queue");
    }

    Queue<int> q10;
    q10.enqueue(1);
    q10.enqueue(2);
    q10.enqueue(3);
    q10.dequeue();
    q10.dequeue();
    q10.enqueue(4);
    q10.enqueue(5);
    assert(q10.size() == 3 && "Circular queue size should be 3");
    assert(q10.front() == 3 && "Circular queue front should be 3");
    assert(q10.back() == 5 && "Circular queue back should be 5");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}