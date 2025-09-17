#include <stack>
#include <vector>
#include <string>

// Leetcode 682

int calPoints(const std::vector<std::string>& operations) {
    std::stack<int> stk;
    for (const auto& op : operations) {
        if (op == "D") {
            stk.push(stk.top() * 2);
        }
        else if (op == "C") {
            stk.pop();
        }
        else if (op == "+") {
            int first = stk.top();
            stk.pop();
            int nw = stk.top() + first;
            stk.push(first);
            stk.push(nw);
        }
        else {
            stk.push(std::stoi(op));
        }
    }

    int summ = 0;
    while (!stk.empty()) {
        summ += stk.top();
        stk.pop();
    }

    return summ;
}