#include "Stack/Array Stack/Stack.hpp"
#include <string>
#include <limits>
#include <cstdlib>
#include <cmath>

long long evaluateRPN(const std::string& expression) {
    if (expression.empty()) {
        return std::numeric_limits<long long>::min(); // should it throw an exception here?
    }

    Stack<long long> stk;
    std::string token;
    for (std::size_t i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ') {
            continue;
        }

        if (std::isdigit(expression[i]) || (expression[i] == '-' && i + 1 < expression.length() && std::isdigit(expression[i + 1]))) {
            token.clear();
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '-')) {
                token += expression[i];
                ++i;
            }

            --i;
            stk.push(std::stoll(token));
        } // unary operations
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            if (stk.size() < 2) {
                return std::numeric_limits<long long>::min();
            }

            long long b = stk.top();
            stk.pop();
            long long a = stk.top();
            stk.pop();

            switch (expression[i]) {
                case '+':
                    stk.push(a + b);
                    break;
                case '-':
                    stk.push(a - b);
                    break;
                case '*':
                    stk.push(a * b);
                    break;
                case '/':
                    if (b == 0) {
                        return std::numeric_limits<long long>::min();
                    }
            
                    stk.push(a / b);
                    break;
                case '^':
                    stk.push(static_cast<long long>(std::pow(a, b)));
                    break;
            }
        }
        else if (expression[i] == '+' || expression[i] == '-') {
            if (stk.empty()) {
                return std::numeric_limits<long long>::min();
            }

            long long top = stk.top();
            stk.pop();
            if (expression[i] == '-') {
                stk.push(-top);
            } 
            else {  
                stk.push(top);
            }
        } 
        else {
            return std::numeric_limits<long long>::min();
        }
    } // binary operations

    if (stk.size() != 1) {
        return std::numeric_limits<long long>::min();
    }

    return stk.top();
}