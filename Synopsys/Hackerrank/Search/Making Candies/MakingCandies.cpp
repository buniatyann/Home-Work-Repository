#include <iostream>
#include <cmath>

/*
    Time O(log(n))
    Space O(1)
    A revision is needed. Further optimize the execution time of the program
*/
long minimumPasses(long m, long w, long p, long n) {
    // If the target is less than or equal to the initial production capacity, return the required passes
    if (n <= p) {
        return ceil(static_cast<double>(n) / (m * w));
    }

    long curr = 0;  // The number of passes taken so far
    long long candy = 0;  // Total amount of candy produced so far
    long ans = LONG_MAX;  // Initialize to a large number

    while (candy < n) {
        // If we don't have enough candy to buy any machines, calculate how many passes are required to gather enough
        if (candy < p) {
            long i = ceil(static_cast<double>(p - candy) / (m * w));
            curr += i;
            candy += m * w * i;
            continue;
        }

        // Buy new machines
        long buy = candy / p;
        candy = candy % p;  // Update remaining candy after buying new machines

        // Calculate the new total machines
        long total = m + w + buy;
        long half = total / 2;

        if (m > w) {
            m = std::max(m, half);
            w = total - m;
        } else {
            w = std::max(w, half);
            m = total - w;
        }

        // One pass to buy the machines
        curr += 1;
        candy += m * w;

        // Update the answer, considering the final number of passes required
        ans = std::min(ans, curr + static_cast<long>(ceil(static_cast<double>(n - candy) / (m * w))));
    }

    // Return the minimum number of passes needed to reach n candy
    return std::min(ans, curr);
}
