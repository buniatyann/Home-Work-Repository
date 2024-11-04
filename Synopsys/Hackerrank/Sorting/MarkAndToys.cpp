#include <bits/stdc++.h>

/*
    Time O(nlogn)
    Space O(1) || O(n)
*/
int maximumToys(std::vector<int> prices, int k) {
    // Sort the prices in ascending order
    std::sort(prices.begin(), prices.end());
    
    int count = 0;      // Initialize the count of toys purchased
    int curr_summ = 0;  // Initialize the current total cost of toys
    
    // Iterate through each toy price
    for(int price : prices) {
        // Check if the current toy can be bought within the budget
        if(price + curr_summ <= k) {
            curr_summ += price;  // Add the price to the current sum
            count += 1;          // Increment the toy count
        } else {
            break;               // Exit the loop if the budget is exceeded
        }
    }
    
    return count;  // Return the total number of toys purchased
}