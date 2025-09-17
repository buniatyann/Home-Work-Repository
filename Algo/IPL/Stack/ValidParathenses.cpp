#include <stack>
#include <unordered_map>
#include <string>

// Leetcode 20
bool isValid(const std::string& s) {
    if (s.empty()) {
        return true;
    }
    
    std::unordered_map<char, char> pairs = {
        {')', '('},
        {'}', '{'},
        {']', '['},
    };
    std::stack<char> stk;
    for (char c : s) {
        if (pairs.find(c) == pairs.end()) {
            stk.push(c);
        }
        else if (stk.empty() || stk.top() != pairs[c]) {
            return false;
        }
        else if (stk.top() == pairs[c]) {
            stk.pop();
        }
    }

    return stk.empty();
}