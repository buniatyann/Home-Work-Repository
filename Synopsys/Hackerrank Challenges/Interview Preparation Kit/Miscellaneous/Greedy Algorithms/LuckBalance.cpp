#include <vector>
#include <iostream>
#include <algorithm>

/*
    Time O(nlog(n))
    Space O(n)
*/
int luckBalance(int k, std::vector<std::vector<int>> contests) {
    // Vector to hold the luck values of important contests
    std::vector<int> important_contests;
    
    // Variable to track total luck (starting with unimportant contests)
    int total_luck = 0;

    // Separate important and unimportant contests
    for (const auto& contest : contests) {
        int luck = contest[0];     // Luck associated with the contest
        int importance = contest[1]; // Importance rating of the contest

        if(importance == 1){
            // If contest is important, add its luck value to important_contests list
            important_contests.push_back(luck);
        } 
        else {
            // If contest is unimportant, add its luck value directly to total_luck
            total_luck += luck;
        }
    }

    // Sort the important contests in descending order to maximize the luck we can gain
    std::sort(important_contests.rbegin(), important_contests.rend());

    // Lose the k most valuable important contests (maximize the luck we gain)
    for (int i = 0; i < k && i < important_contests.size(); ++i) {
        total_luck += important_contests[i]; // Add luck for the contests we decide to lose
    }

    // Win the remaining important contests (reduce our luck)
    for (int i = k; i < important_contests.size(); ++i) {
        total_luck -= important_contests[i]; // Subtract luck for the contests we have to win
    }

    // Return the final total luck balance
    return total_luck;
}