#include <bits/stdc++.h>


/*
    Time(mlogD) where m is the number of machines and D is the range of days we are searching over.
    Space O(1)
*/
long minTime(std::vector<long> machines, long goal) {
    // Helper lambda to calculate total production in 'days'
    auto total_production = [&](long days) {
        long total = 0;
        for (long m : machines) {
            total += days / m; // Calculate how many items each machine produces in 'days'
        }
        return total;
    };

    // Setting initial bounds for binary search
    long lower_bound = 1; // Minimum 1 day to produce
    long upper_bound = *std::min_element(machines.begin(), machines.end()) * goal; // Worst case

    // Binary search for the minimum time
    while (lower_bound < upper_bound) {
        long mid = lower_bound + (upper_bound - lower_bound) / 2;
        long produced = total_production(mid); // Calculate total production in 'mid' days
        
        if (produced >= goal) {
            upper_bound = mid; // Can produce enough, try for fewer days
        } else {
            lower_bound = mid + 1; // Not enough, need more days
        }
    }

    return lower_bound; // This will be the minimum days required
}