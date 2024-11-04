#include <bits/stdc++.h>

/*
    Time O(n)
    Space O(n)
*/
long largestRectangle(std::vector<int> h) {
    std::stack<int> heights; // Stack to store indices of histogram bars
    long max = 0; // Variable to keep track of the maximum area found
    int n = h.size(); // Number of bars in the histogram
    
    // Iterate through each bar, plus an additional iteration for the final zero height
    for (int i = 0; i <= n; ++i) {
        // Use 0 height at the end to ensure we clear the stack at the end
        int height = (i == n) ? 0 : h[i];
        
        // While there are bars in the stack and the current height is less than
        // the height of the bar at the top of the stack
        while (!heights.empty() && h[heights.top()] > height) {
            // Get the index of the top bar
            int ind_h = heights.top();
            heights.pop(); // Remove the top bar
            
            // Calculate the width of the rectangle
            // If the stack is empty, it means the popped bar was the smallest so far,
            // thus its width extends to the current index (i)
            // Otherwise, it extends from the next top index to the current index
            long area = static_cast<long>(h[ind_h]) * (heights.empty() ? i : i - heights.top() - 1);
            
            // Update the maximum area found
            max = std::max(max, area);
        }
        
        // Push the current index onto the stack
        heights.push(i);
    }
    
    return max; // Return the maximum area found
}