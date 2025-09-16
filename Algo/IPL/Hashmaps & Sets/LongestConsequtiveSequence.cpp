#include <vector>
#include <set>
#include <unordered_set>

// Leetcode 128

int longestConsecutive(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    std::set<int> st(nums.begin(), nums.end());
    auto prev = st.begin();
    int max_len = 0;
    int curr_len = 1;
    for (auto it = std::next(prev); it != st.end(); ++it) {
        if (*it - *prev == 1) {
            ++curr_len;
        }
        else {
            max_len = std::max(curr_len, max_len);
            curr_len = 1;
        }

        ++prev;
    }

    max_len = std::max(max_len, curr_len);
    return max_len;
}

int longestConsecutive(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    std::unordered_set<int> num_set(nums.begin(), nums.end());
    int max_len = 1;

    for (int num : num_set) {
        if (num_set.find(num - 1) == num_set.end()) {
            int curr_len = 1;
            while (num_set.find(num + curr_len) != num_set.end()) {
                ++curr_len;
            }

            max_len = std::max(max_len, curr_len);
        }
    }

    return num_set.empty() ? 0 : max_len;
}