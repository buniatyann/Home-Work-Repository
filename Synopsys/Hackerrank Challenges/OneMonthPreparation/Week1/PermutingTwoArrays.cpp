#include <algorithm>
#include <vector>
#include <string>

/*
    Time O(n * log(n))
    Space O(n)
*/
std::string twoArrays(int k, std::vector<int> A, std::vector<int> B) {
    if (A.size() != B.size()) {
        return "NO";
    }

    // Sort A in ascending order and B in descending order
    std::sort(A.begin(), A.end());
    std::sort(B.rbegin(), B.rend());

    // Check if the sum of corresponding elements is at least k
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] + B[i] < k) {
            return "NO";
        }
    }

    // If all conditions are met, return "YES"
    return "YES";
}
