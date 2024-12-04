import os 
import math
import re 
import sys

# Time O(log(n))
# Space O(1)
# veranayel
def minimumPasses(m, w, p, n):
    # Base case: if the target is less than or equal to the initial production
    if n <= p:
        return math.ceil(n / (m * w))  # Return the minimum passes needed to reach n candies
    
    curr = candies = 0  # `curr` keeps track of the number of passes made, `candies` tracks the total candies
    ans = float('inf')  # Initialize the answer to infinity, so we can minimize it during the process
    
    # While we don't have enough candies to reach `n`
    while candies < n:
        
        # If we don't have enough candies to buy any machines, calculate the number of passes needed
        if candies < p:
            # How many passes do we need to gather enough candies to buy at least one machine?
            i = math.ceil((p - candies) / (m * w))  # Calculate number of passes to accumulate enough candies
            curr += i  # Increase the number of passes
            candies += m * w * i  # Update the total candies collected
            continue  # Proceed to the next iteration, since we are gathering candies
        
        # Now that we have enough candies to buy new machines, calculate how many we can buy
        buy, candies = divmod(candies, p)  # `buy` is how many machines we can buy, `candies` is the remainder
        
        # Update the total number of machines (`m` + `w` + `buy` machines bought)
        total = m + w + buy
        half = total // 2  # The ideal distribution is as balanced as possible
        
        # Balance the number of machines and workers to maximize production
        if m > w:
            m = max(m, half)
            w = total - m
        else:
            w = max(w, half)
            m = total - w

        # One pass to buy new machines
        curr += 1
        candies += m * w  # Increase the total candies produced in the next pass
        
        # Update the answer: check how many more passes are required to reach `n` from the current state
        ans = min(ans, curr + math.ceil((n - candies) / (m * w)))

    # Return the minimum number of passes required
    return min(ans, curr)