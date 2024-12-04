#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <limits.h>

/*
    Time O(n)
    Space O(n)
    veranayel
*/
std::vector<long> riddle(const std::vector<long>& arr) {
    int n = arr.size();
    std::vector<int> left(n), right(n);
    std::vector<long> result(n + 1, LONG_MIN);  // Stores maximum minimums for each window size

    // Calculate left distances (distance to previous smaller element for each element)
    std::stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }
        // If stack is empty, there is no smaller element on the left
        left[i] = stk.empty() ? i + 1 : i - stk.top();
        stk.push(i);
    }

    // Clear stack to reuse for right distances
    while (!stk.empty()) stk.pop();

    // Calculate right distances (distance to next smaller element for each element)
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }
        // If stack is empty, there is no smaller element on the right
        right[i] = stk.empty() ? n - i : stk.top() - i;
        stk.push(i);
    }

    // Use left and right distances to calculate window minimums
    for (int i = 0; i < n; ++i) {
        int window_size = left[i] + right[i] - 1;  // Maximum window size where arr[i] is the minimum
        result[window_size] = std::max(result[window_size], arr[i]);  // Maximize the minimum for this window size
    }

    // Ensure result is non-increasing
    for (int i = n - 1; i >= 1; --i) {
        result[i] = std::max(result[i], result[i + 1]);
    }

    // Return result from index 1 to n (index 0 is unused)
    return std::vector<long>(result.begin() + 1, result.end());
}
