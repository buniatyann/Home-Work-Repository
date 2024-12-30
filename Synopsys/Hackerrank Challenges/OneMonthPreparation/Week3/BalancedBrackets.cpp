#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>

/*
    Time O(n)
    Space O(n)
*/
std::string isBalanced(const std::string& s) {
    // Check if the input string is empty
    if (s.empty()) return "YES";
    
    // Mapping closing brackets to their corresponding opening brackets
    std::unordered_map<char, char> mp = {
        {')', '('},
        {']', '['},
        {'}', '{'},
    };
    
    // Stack to hold the opening brackets
    std::stack<char> stk;
    
    // Iterate through each character in the string
    for (auto ch : s) {
        // If the stack is empty and we encounter a closing bracket
        if (stk.empty() && mp.find(ch) != mp.end()) {
            return "NO"; // Unbalanced
        }
        // If the character is a closing bracket and does not match the top of the stack
        else if (mp.find(ch) != mp.end() && stk.top() != mp[ch]) {
            return "NO"; // Unbalanced
        }
        // If the character is a closing bracket and matches the top of the stack
        else if (mp.find(ch) != mp.end() && stk.top() == mp[ch]) {
            stk.pop(); // Pop the matched opening bracket
        }
        // If the character is an opening bracket, push it onto the stack
        else {
            stk.push(ch);
        }
    }
    
    // If the stack is empty, all brackets were matched and balanced, else not
    return stk.empty() ? "YES" : "NO";
}

/*
    Time O(n)
    Space O(n)
*/
std::string isBalanced(const std::string& s) {
    // Stack to hold opening brackets
    std::stack<char> stk;
    
    // Iterate through each character in the string
    for (char ch : s) {
        // If it's an opening bracket, push it onto the stack
        if (ch == '(' || ch == '[' || ch == '{') {
            stk.push(ch);
        }
        // If it's a closing bracket, check if it matches the top of the stack
        else if (ch == ')' || ch == ']' || ch == '}') {
            // If the stack is empty or top of the stack doesn't match, return "NO"
            if (stk.empty()) return "NO";
            char top = stk.top();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return "NO";
            }
            stk.pop(); // Pop the matching opening bracket
        }
    }
    
    // If the stack is empty, all brackets matched; otherwise, it's unbalanced
    return stk.empty() ? "YES" : "NO";
}