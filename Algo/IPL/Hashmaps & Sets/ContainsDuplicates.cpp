#include <vector>
#include <unordered_set>

// Leetcode 217
bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> st(nums.begin(), nums.end());
    // for (int i : nums) {
    //     if (st.find(i) != st.end()) {
    //         return true;
    //     }

    //     st.insert(i);
    // }

    // return false;
    return st.size() != nums.size();
}