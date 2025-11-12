#include <stack>
#include <type_traits>
#include <cassert>

template <typename T>
std::stack<T> mergeStacks(const std::stack<T>& A, const std::stack<T>& B) {
    static_assert(std::is_arithmetic_v<T>, "mergeStacks: stack value type must be arithmetic");

    std::stack<T> stk1 = A;
    std::stack<T> stk2 = B;
    std::stack<T> ans;
    while (!stk1.empty() && !stk2.empty()) {
        if (stk1.top() >= stk2.top()) {
            ans.push(stk1.top());
            stk1.pop();
        }
        else {
            ans.push(stk2.top());
            stk2.pop();
        }
    }

    while (!stk1.empty()) {
        ans.push(stk1.top());
        stk1.pop();
    }

    while (!stk2.empty()) {
        ans.push(stk2.top());
        stk2.pop();
    }

    return ans;
}