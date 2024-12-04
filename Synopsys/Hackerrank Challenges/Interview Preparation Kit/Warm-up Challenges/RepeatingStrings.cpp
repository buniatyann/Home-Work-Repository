#include <string>

/*
    Time O(n)
    Space O(1)
*/
long repeatedString(std::string s, long n) {
    // Count the occurrences of 'a' in the original string s
    int count_s = 0;
    for (char i : s) {
        if (i == 'a') {
            ++count_s;  // Increment count_s whenever 'a' is found in s
        }
    }
    
    // Calculate the number of full repetitions of s in the first n characters
    long reminder = n % s.length();  // The remainder when n is divided by the length of s
    long repeats = n / s.length();  // Number of full repetitions of s that fit in n
    
    // Count 'a's in the full repetitions of the string s
    long count = count_s * repeats;  // Multiply the number of 'a's in s by the number of full repeats

    // Count 'a's in the partial repetition (the first "reminder" characters of s)
    for (long i = 0; i < reminder; ++i) {
        if (s[i] == 'a') {
            ++count;  // Increment count for each 'a' found in the partial repetition
        }
    } 
    
    // Return the total count of 'a's in the first n characters of the repeated string
    return count;
}
