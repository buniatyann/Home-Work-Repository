#include <algorithm>
#include <iostream>

/*
    Time O(1)
    Space O(1)
*/
// Function to calculate the minimum number of page flips
// n - total number of pages in the book
// p - the target page to reach
int pageCount(int n, int p) {
    // If the target page is either the first or the last page, no flips are needed
    if (p == 1 || p == n) {
        return 0;  // No need to flip if the target page is the first or last page
    }
    
    // Calculate flips from the front of the book:
    // (p) / 2 calculates the number of flips to reach page p starting from page 1
    // We divide by 2 because each flip moves us by 2 pages (e.g., 1 -> 2, 2 -> 3, etc.)
    int front = p / 2;
    
    // Calculate flips from the back of the book:
    // (n) / 2 calculates the number of flips to reach page n from the back (starting from n)
    // (p) / 2 calculates the number of flips to reach page p from the front.
    // Subtracting the two values gives us the number of flips to reach p from the back.
    int back = (n / 2) - (p / 2);
    
    // Return the minimum of flips from the front and flips from the back
    return std::min(front, back);
}
