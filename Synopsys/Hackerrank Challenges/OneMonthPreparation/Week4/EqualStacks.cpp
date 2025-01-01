#include <vector>
#include <algorithm>
#include <iostream>

/*
    Time O(n + m + k)
    Space O(n + m + k)
    where n, m, and k are the sizes of the three stacks
    veranayel
*/
int equalStacks(std::vector<int> h1, std::vector<int> h2, std::vector<int> h3) {
    // Initializing the variables to hold the total height of each stack.
    int l1 = 0, l2 = 0, l3 = 0;
    
    // Summing up the heights of the stacks (l1, l2, l3 are the total heights of each stack).
    for(int i : h1) {
        l1 += i;  // Sum the elements of the first stack (h1).
    }
    for(int i : h2) {
        l2 += i;  // Sum the elements of the second stack (h2).
    }
    for(int i : h3) {
        l3 += i;  // Sum the elements of the third stack (h3).
    }
    
    // This loop will continue until either one of the stacks is empty, or the heights of the three stacks match.
    while (l1 != 0 && l2 != 0 && l3 != 0 && (l1 != l2 || l2 != l3)) {
        // We find the largest height and remove the top element from the corresponding stack.
        if (std::max({l1, l2, l3}) == l1) {
            // Remove the top element from the first stack and subtract its value from l1.
            l1 -= h1[0];
            h1.erase(h1.begin());  // Remove the first element of h1.
        } else if (std::max({l1, l2, l3}) == l2) {
            // Remove the top element from the second stack and subtract its value from l2.
            l2 -= h2[0];
            h2.erase(h2.begin());  // Remove the first element of h2.
        } else {
            // Remove the top element from the third stack and subtract its value from l3.
            l3 -= h3[0];
            h3.erase(h3.begin());  // Remove the first element of h3.
        }
    }
    
    // If all three stacks have equal height, return the height (l1 == l2 == l3).
    // Otherwise, return 0 if they are not equal.
    return (l1 == l2 && l2 == l3) ? l1 : 0;
}
