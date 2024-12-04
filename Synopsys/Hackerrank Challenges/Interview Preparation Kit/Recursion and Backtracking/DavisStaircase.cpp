#include <iostream>
#include <vector>

/*
    Time O(n)
    Space O(n)
*/
int stepPerms(int n) {
    // Base cases: If n is 0 or 1, there's only one way to stay at the ground or reach the 1st step.
    if (n == 0 || n == 1) return 1; // 1 way to stay at the ground or reach the first step.
    
    // For n = 2, there are 2 possible ways to reach the second step: (1+1) or (2).
    if (n == 2) return 2; // 2 ways to reach the 2nd step: (1+1) or (2).

    // Initialize a vector `stairs` where `stairs[i]` will store the number of ways to reach the i-th step.
    std::vector<int> stairs(n + 1);
    
    // Base cases initialization:
    stairs[0] = 1; // There is 1 way to stay at the ground (do nothing).
    stairs[1] = 1; // 1 way to reach the 1st step (a single step of size 1).
    stairs[2] = 2; // 2 ways to reach the 2nd step (1+1 or 2).

    // Fill the rest of the `stairs` array using the dynamic programming relation:
    // stairs[i] = stairs[i-1] + stairs[i-2] + stairs[i-3]
    // This is because you can reach step i by:
    // 1. Taking a step of size 1 from step i-1
    // 2. Taking a step of size 2 from step i-2
    // 3. Taking a step of size 3 from step i-3
    for (int i = 3; i <= n; ++i) {
        stairs[i] = stairs[i - 1] + stairs[i - 2] + stairs[i - 3]; // Sum of ways to reach i-1, i-2, and i-3
    }
    
    // The final answer is the number of ways to reach the nth step.
    return stairs[n];
}
