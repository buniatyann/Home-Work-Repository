#include <bits/stdc++.h>

/*
    Time O(n * d)
    Space O(d)
    Veranayel
*/
int activityNotifications(std::vector<int> expenditure, int d) {
    int res = 0;
    std::vector<int> hlp(expenditure.begin(), expenditure.begin() + d);

    // Sort the initial trailing data
    std::sort(hlp.begin(), hlp.end());

    for (int i = d; i < expenditure.size(); ++i) {
        // Calculate the median
        double median;
        
        if (d % 2 == 0) {
            median = (hlp[d / 2 - 1] + hlp[d / 2]) / 2.0;
        } else {
            median = hlp[d / 2];
        }

        // Check if the current expenditure is greater than or equal to twice the median
        if (expenditure[i] >= 2 * median) {
            ++res;
        }

        // Update the trailing data for the next iteration
        // Remove the oldest value
        auto it = std::lower_bound(hlp.begin(), hlp.end(), expenditure[i - d]);
        hlp.erase(it);

        // Insert the new expenditure while maintaining sorted order
        hlp.insert(std::lower_bound(hlp.begin(), hlp.end(), expenditure[i]), expenditure[i]);
    }

    return res;
    
}