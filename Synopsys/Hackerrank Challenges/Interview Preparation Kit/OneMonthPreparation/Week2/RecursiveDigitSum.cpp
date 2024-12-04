#include <string>
#include <cctype>

/*
    Time O(n + log10(num))
    Space O(n + log10(num))
*/
// Helper function to compute the sum of digits recursively
int digit_sum(int num){
    // Base case: if num is less than 10, return the number itself
    if(num < 10){
        return num;
    }
    
    int sum = 0;
    
    // While there are digits left in num, sum them
    while(num){
        sum += num % 10;  // Add the last digit of num
        num /= 10;         // Remove the last digit of num
    }
    
    // Recursively call digit_sum with the sum of digits
    return digit_sum(sum);
}

// Function to calculate the super digit of a large number represented by string n
int superDigit(std::string n, int k) {
    int sum = 0;
    
    // Calculate the sum of digits of the string n
    for(char c : n){
        sum += c - '0';  // Convert character to integer and add to sum
    }
    
    // Multiply the sum of digits by k and pass it to digit_sum to find the super digit
    return digit_sum(sum * k);
}
