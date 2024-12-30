#include <vector>
#include <iostream>

const std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

/*
    Time O(n * q) where n is the number of plates and q is the number of prime numbers.
    Space O(n)
*/
std::vector<int> waiter(std::vector<int>& number, int q) {
    // The answer array where the final result (stacked plates) will be stored
    std::vector<int> answer;

    // Initial stack of plates (we use this for processing)
    std::vector<int> a = number;

    // Loop through each prime number (up to q primes)
    for (int i = 0; i < q; ++i) {
        // Temporary stack for non-divisible plates
        std::vector<int> temp;
        // Stack for divisible plates
        std::vector<int> b;

        // Process each plate in stack 'a'
        while (!a.empty()) {
            // Take the top plate from stack 'a'
            int val = a.back();
            a.pop_back(); // Remove the top plate

            // Check if the plate is divisible by the current prime
            if (val % primes[i] == 0) {
                // If divisible, push it onto stack 'b'
                b.push_back(val);
            } 
            else {
                // Otherwise, push it onto the temporary stack 'aTemp'
                temp.push_back(val);
            }
        }

        // Push all plates from stack 'b' (divisible plates) to the answer
        while (!b.empty()) {
            answer.push_back(b.back());
            b.pop_back(); // Remove plates from stack 'b'
        }

        // Now update stack 'a' to the remaining plates (those not divisible by the current prime)
        a = temp;
    }

    // Add any remaining plates from 'a' to the answer (plates that couldn't be divided by any prime)
    while (!a.empty()) {
        answer.push_back(a.back());
        a.pop_back(); // Remove the plates from stack 'a'
    }

    // Return the final order of plates in answer array
    return answer;
}
