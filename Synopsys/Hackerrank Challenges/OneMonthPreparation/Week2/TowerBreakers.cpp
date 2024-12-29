#include <iostream>

/*
    Time O(1)
    Space O(1)
*/
int towerBreakers(int n, int m) {
    // If the height of the towers is 1, no moves can be made, so the second player always wins (output 2).
    // If the number of towers is even, the second player always wins, as the game will eventually result in a symmetric position.
    // Otherwise, if the number of towers is odd and the height is greater than 1, the first player can always win (output 1).
    
    return (m == 1 || n % 2 == 0) ? 2 : 1;
}