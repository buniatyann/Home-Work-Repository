#include <string>
#include <unordered_map>

int romanToInt(const std::string& s) {
    int summ = 0;
    std::unordered_map<char, int> mp = {
        {'I' , 1},
        {'V' , 5},
        {'X' , 10},
        {'L' , 50},
        {'C' , 100},
        {'D' , 500},
        {'M' , 1000},
    };
    
    for (std::size_t i = 0; i < s.length(); ++i) {
        if (i + 1 < s.length() && mp[s[i]]  < mp[s[i + 1]]) {
            summ -= mp[s[i]];
        }
        else {
            summ += mp[s[i]];
        }
    }

    return summ;
}
