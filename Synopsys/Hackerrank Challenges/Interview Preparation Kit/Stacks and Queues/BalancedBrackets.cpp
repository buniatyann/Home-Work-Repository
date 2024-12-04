#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

/*
    Time O(n)
    Space O(n)
*/
std::string isBalanced(std::string& s) {
    const std::unordered_map<char, char> pairs = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}
    };
    
    std::stack<char> stk;
    
    for (char c : s) {
        // If the character is an opening bracket, push it onto the stack
        if(pairs.find(c) != pairs.end()){
            stk.push(c);
        }
        // If the character is a closing bracket
        else{
            // Check if the stack is empty or the top doesn't match
            if (stk.empty() || pairs.at(stk.top()) != c) {
                return "NO"; // Unmatched closing bracket
            }
            stk.pop(); // Match found, pop the stack
        }
    }
    
    // If the stack is empty, all brackets matched; otherwise, they're unbalanced
    return stk.empty() ? "YES" : "NO"; 
}