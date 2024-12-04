#include <bitset>
#include <vector>
#include <string>
#include <cctype>  

/*
    Time O(n)
    Space O(1)
*/
std::string checkPangram(const std::string& s) {
    std::bitset<26> bits;  // bitset to track presence of each letter

    // Loop through each character in the string
    for(char c : s) {
        if(std::isalpha(c)){
            bits.set(std::tolower(c) - 'a');  // Mark the bit corresponding to the letter
        }
    }

    // If all bits are set, it means all letters are present
    if (bits.count() == 26) {
        return "pangram";
    }

    return "not pangram";
}


/*
    Time O(n)
    Space O(1)
*/
std::string checkPangram(const std::string& s) {
    // A vector of size 26 to track if each letter appears in the string
    std::vector<bool> vec(26, false);

    // Loop through each character in the string
    for (char c : s) {
        // Convert to lowercase and check if the character is a letter
        if(std::isalpha(c)){
            vec[std::tolower(c) - 'a'] = true;  // Mark the letter as present
        }
    }
    
    // Check if all letters are present
    for (bool present : vec) {
        if(!present){  // If any letter is missing
            return "not pangram";
        }
    }
    
    return "pangram";
}
