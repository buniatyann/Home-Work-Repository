#include <stack>
#include <vector>
#include <string>

// Leetcode 150

int evalRPN(const std::vector<std::string>& tokens) {
    int ans = 0;
    std::stack<int> stk;
    for (const auto& token : tokens) {
        if (token == "-") {
            int first = stk.top();
            stk.pop();
            int second = stk.top();
            stk.pop();
            stk.push(second - first);
        }
        else if (token == "+") {
            int first = stk.top();
            stk.pop();
            int second = stk.top();
            stk.pop();
            stk.push(second + first);
        }
        else if (token == "*") {
            int first = stk.top();
            stk.pop();
            int second = stk.top();
            stk.pop();
            stk.push(second * first);
        }
        else if (token == "/") {
            int first = stk.top();
            stk.pop();
            int second = stk.top();
            stk.pop();
            stk.push(second / first);
        }
        else {
            stk.push(std::stoi(token));
        }
    }

    return stk.top();
}