#include <stack>
#include <iostream>


/*
    Time O(1) for all functions
    Space O(n) for all functions
*/
class MyQueue {
public:
    // Two stacks: one to hold new elements and one to maintain the order of the queue
    std::stack<int> stack_newest_on_top, stack_oldest_on_top;

    // Push element x to the back of the queue.
    void push(int x) {
        stack_newest_on_top.push(x);  // Push new element onto stack_newest_on_top
    }

    // Remove the element from the front of the queue.
    void pop() {
        // Move elements to stack_oldest_on_top if it's empty
        helper();
        // Remove the top element from stack_oldest_on_top if it has elements
        if (!stack_oldest_on_top.empty()) {
            stack_oldest_on_top.pop();
        }
    }

    // Get the front element.
    int front() {
        // Move elements to stack_oldest_on_top if it's empty
        helper();
        // Return the top of stack_oldest_on_top, which is the front of the queue
        return stack_oldest_on_top.top();
    }

private:
    // Helper function to transfer elements from stack_newest_on_top to stack_oldest_on_top
    // This ensures the oldest element in the queue is on top of stack_oldest_on_top
    void helper() {
        if (stack_oldest_on_top.empty()) {
            // Transfer all elements from stack_newest_on_top to stack_oldest_on_top
            while (!stack_newest_on_top.empty()) {
                stack_oldest_on_top.push(stack_newest_on_top.top());
                stack_newest_on_top.pop();
            }
        }
    }
};
