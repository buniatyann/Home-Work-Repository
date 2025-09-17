#include <stack>

// Leetcode 155 needs to be reviewed

class MinStack {
public:
    MinStack() {
    }
    
    void push(int val) {
        main.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (!main.empty()) {
            if (main.top() == minStack.top()) {
                minStack.pop();
            }
            main.pop();
        }
    }
    
    int top() {
        if (!main.empty()) {
            return main.top();
        }

        return -1;
    }
    
    int getMin() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        
        return -1;
    }

private:
    std::stack<int> main;
    std::stack<int> minStack;
};