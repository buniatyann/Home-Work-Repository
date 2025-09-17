#include <stack>
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    std::vector<int> ans(temperatures.size(), 0);
    std::stack<std::vector<int>> stk;
    for (int i = 0; i < temperatures.size(); ++i) {
        if (stk.empty()) {
            stk.push({temperatures[i], i});
        }
        else {
            if (temperatures[i] > stk.top()[0]){
                while (!stk.empty() && temperatures[i] > stk.top()[0]) {
                    ans[stk.top()[1]] = i - stk.top()[1];
                    stk.pop();
                }
                
                stk.push({temperatures[i], i});
            }
            else {
                stk.push({temperatures[i], i});
            }
        }
    }

    return ans;
}