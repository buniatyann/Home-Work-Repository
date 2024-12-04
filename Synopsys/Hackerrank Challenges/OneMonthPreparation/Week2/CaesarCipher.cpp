#include <string>
#include <cstring>

/*
    Time O(n)
    Space O(n) why?
*/
std::string caesarCipher(std::string s, int k) {
    k %= 26;  // Normalize the shift to be within 0-25

    for (char &c : s) {  // Use a reference to modify characters directly in the string
        if (!std::isalpha(c)) continue;  // Skip non-alphabetic characters
        
        if ('a' <= c && c <= 'z') {
            c = 'a' + (c - 'a' + k) % 26;  // Shift lowercase letters
        } 
        else if ('A' <= c && c <= 'Z') {
            c = 'A' + (c - 'A' + k) % 26;  // Shift uppercase letters
        }
    }

    return s;  // Return the modified string
}