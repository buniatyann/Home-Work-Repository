#include <unordered_map>
#include <string>
#include <boost/unordered_map.hpp>

/*
    Time O(n)
    Space O(1)
*/
int countingValleys(int steps, std::string path) {
    boost::unordered_map<char, int> directions = {
        {'U', 1},  // 'U' means going up, increase elevation by 1
        {'D', -1}  // 'D' means going down, decrease elevation by 1
    };

    int valleys = 0;  // To count the number of valleys
    int elevation = 0; // To track the current elevation of the hiker

    // Iterate through each step in the path string
    for (char step : path) {
        // Update the current elevation based on the step
        elevation += directions[step];
        
       // Check if we have just returned to sea level after going below it (completing a valley)
       if (elevation == 0 && step == 'U') {
           ++valleys;  // Increment valley count when coming back to sea level after an 'Up' step
       }
   }
   
   return valleys;  // Return the total number of valleys encountered
}

/*
    Time O(n)
    Space O(10)
*/
int countingValleys(int steps, std::string path) {
    // Create a map to convert 'U' (Up) to +1 and 'D' (Down) to -1
    std::unordered_map<char, int> directions = {
        {'U', 1},  // 'U' means going up, increase elevation by 1
        {'D', -1}  // 'D' means going down, decrease elevation by 1
    };

    int valleys = 0;  // To count the number of valleys
    int elevation = 0; // To track the current elevation of the hiker

    // Iterate through each step in the path string
    for (char step : path) {
        // Update the current elevation based on the step
        elevation += directions[step];
        
        // Check if we have just returned to sea level after going below it (completing a valley)
        if (elevation == 0 && step == 'U') {
            ++valleys;  // Increment valley count when coming back to sea level after an 'Up' step
        }
    }
    
    return valleys;  // Return the total number of valleys encountered
}
