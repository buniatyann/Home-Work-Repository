#include <iostream>

/*
    Time O(2 ^ n)
    Space O(n)
*/
int fibonacci(int n) {
    // Base case: If n is 0 or 1, return n (as Fibonacci(0) = 0 and Fibonacci(1) = 1)
    if(n == 0 || n == 1){
        return n;
    }
    
    // Base case: If n is 2, return 1 (since Fibonacci(2) = 1)
    if(n == 2){
        return 1;
    }
    
    // Recursive case: Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
    Time O(n)
    Space O(1);
*/
int fibonacci(int n) {
    // Base cases
    if (n == 0 || n == 1) {
        return n;
    }

    int prev2 = 0;  // Fibonacci(0)
    int prev1 = 1;  // Fibonacci(1)
    int current;

    // Calculate Fibonacci numbers from 2 to n
    for (int i = 2; i <= n; ++i) {
        current = prev1 + prev2;  // Fibonacci(i) = Fibonacci(i-1) + Fibonacci(i-2)
        prev2 = prev1;  // Update prev2 to previous Fibonacci number
        prev1 = current;  // Update prev1 to the current Fibonacci number
    }

    // Return the nth Fibonacci number
    return current;
}

