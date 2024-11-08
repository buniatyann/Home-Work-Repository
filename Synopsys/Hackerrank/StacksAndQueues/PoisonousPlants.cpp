#include <vector>
#include <stack>
#include <algorithm>

/*
    Time O(n)
    Space O(n)
*/
int poisonousPlants(const std::vector<int>& p) {
    int n = p.size();
    std::vector<int> days(n, 0);  // Stores the days each plant takes to die
    std::stack<int> stk;           // Stack to store the index of each plant
    int max_days = 0;              // Track the maximum days any plant takes to die

    for (int i = 0; i < n; ++i) {
        int day_count = 0;
        
        // Pop plants with higher pesticide levels to the left, updating days
        while (!stk.empty() && p[i] <= p[stk.top()]) {
            day_count = std::max(day_count, days[stk.top()]);
            stk.pop();
        }

        // Only increment days if there are plants to the left with a smaller pesticide level
        if (!stk.empty()) {
            days[i] = day_count + 1;
        }

        // Track the maximum days
        max_days = std::max(max_days, days[i]);
        
        // Push the current plant index onto the stack
        stk.push(i);
    }

    return max_days;
}
