#include <bits/stdc++.h>


void checkMagazine(std::vector<std::string> magazine, std::vector<std::string> note) {
    std::map<std::string, int> word_count;

    // Count occurrences of each word in the magazine
    for (const auto& word : magazine) {
        word_count[word]++;
    }

    // Check if we can construct the note using the words from the magazine
    for (const auto& word : note) {
        if (word_count[word] > 0) {
            word_count[word]--; // Use this word
        } 
        else {
            std::cout << "No" << std::endl;
            return; // Early exit if we can't find a word
        }
    }

    std::cout << "Yes" << std::endl; // If we successfully found all words
}
