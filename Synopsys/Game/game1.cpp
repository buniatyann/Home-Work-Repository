#include "game.h"

Game::Game() : board{0}, turn(1), score(0) {
    // Settting random initial tiles
    // First tile
    int i=rand() % BSIZE;
    int j=rand() % BSIZE;
    board[i][j] = 2;

    // Second  tile
    add_new_tile();
}

void Game::step(char & input) {
    bool valid_step = false; // to keep track if the board is changed
    // 1) move empty tiles
    move(input, valid_step);
    // 2) combine adjacent tiles (if equal)
    combine(input, valid_step);

    if (valid_step) {
        // 3) move empty tiles (again)
        move(input, valid_step);
        // 4) add a new tile
        add_new_tile();
        ++turn;
    }
}

bool Game::move(char& input, bool& valid_step) {
    switch (input) {
    case 'w': // Move UP
        for (int j = 0; j < BSIZE; ++j) { // Parse board from left to right
            for (int i = 0; i < BSIZE; ++i) { // Parse board from top to bottom
                if (board[i][j] == 0) {  // If tile is empty, then shift tiles below
                    for (int k = i + 1; k < BSIZE; ++k) { // Parsing all below tiles to shift (in same order)
                        if (board[k][j] != 0) { // Only move non-empty tiles
                            valid_step = true;
                            board[i][j] = board[k][j]; // SHIFT to the empty tile
                            board[k][j] = 0;
                            break; // Breaking from this inner loop - i.e. shifting only one tile at a time
                        }
                    }
                }
            }
        }
    break;

    case 's': // Move DOWN
        for (int j = 0; j < BSIZE; ++j) { // Parse board from left to right
            for (int i = BSIZE - 1; i >= 0; --i) { // Parse board from bottom to top
                if (board[i][j] == 0) { 
                    for (int k = i - 1; k >= 0; --k) { 
                        if (board[k][j] != 0) { 
                            valid_step = true;
                            board[i][j] = board[k][j]; 
                            board[k][j] = 0;
                            break; 
                        }
                    }
                }
            }
        }
    break;

    case 'a': // Move LEFT
        for (int i = 0; i < BSIZE; ++i) { // Parse board from top to bottom
            for (int j = 0; j < BSIZE; ++j) { // Parse board from left to right
                if (board[i][j] == 0) {
                    for (int k = j + 1; k < BSIZE; ++k) {
                        if (board[i][k] != 0) {
                            valid_step = true;
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            break;
                        }
                    }
                }
            }
        }
    break;

    case 'd': // Move RIGHT
        for (int i = 0; i < BSIZE; ++i) { // Parse board from top to bottom
            for (int j = BSIZE - 1; j >= 0; --j) { // Parse board from right to left
                if (board[i][j] == 0) {
                    for (int k = j - 1; k >= 0; --k) {
                        if (board[i][k] != 0) {
                            valid_step = true;
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            break;
                        }
                    }
                }
            }
        }
        break;
    }

    return valid_step;
}

bool Game::combine(char& input, bool& valid_step) {
    switch (input) {
    case 'w': // Move UP
        for (int j = 0; j < BSIZE; ++j) { // Parse board from left to right
            for (int i = 0; i < BSIZE - 1; ++i) { // Parse board from top to bottom
                // If a tile is not empty and equal to the tile below it
                if ((board[i][j] != 0) && (board[i][j] == board[i + 1][j])) {
                    // Combine these tiles
                    valid_step = true;
                    board[i][j] *= 2; 
                    board[i + 1][j] = 0;
                    score += board[i][j];
                }
            }
        }
    break;

    case 's': // Move DOWN
        for (int j = 0; j < BSIZE; ++j) { // Parse board from left to right
            for (int i = BSIZE - 1; i >= 1; --i) { // Parse board from bottom to top
                if ((board[i][j] != 0) && (board[i][j] == board[i - 1][j])) {
                    valid_step = true;
                    board[i][j] *= 2;
                    board[i - 1][j] = 0;
                    score += board[i][j];
                }
            }
        }
    break;

    case 'a': // Move LEFT
        for (int i = 0; i < BSIZE; ++i) { // Parse board from top to bottom
            for (int j = 0; j < BSIZE - 1; ++j) { // Parse board from left to right
                if ((board[i][j] != 0) && (board[i][j] == board[i][j + 1])) {
                    valid_step = true;
                    board[i][j] *= 2;
                    board[i][j + 1] = 0;
                    score += board[i][j];
                }
            }
        }
    break;

    case 'd': // Move RIGHT
        for (int i = 0; i < BSIZE; ++i) { // Parse board from top to bottom
            for (int j = BSIZE - 1; j >= 1; --j) { // Parse board from right to left
                if ((board[i][j] != 0) && (board[i][j] == board[i][j - 1])) {
                    valid_step = true;
                    board[i][j] *= 2;
                    board[i][j - 1] = 0;
                    score += board[i][j];
                }
            }
        }
    break;
    
    default: std::cout << "Wrong input ('w', 'a', 's' or 'd' only)" << std::endl
                  << "To exit input '.'" << std::endl
                  << "Try again: " << std::endl << std::endl;
    }

    return valid_step;
}

void Game::add_new_tile() {
    std::vector<std::pair<int, int>> empty_tiles; // list of empty tiles

    for (int i = 0; i < Game::BSIZE; ++i) {
        for (int j = 0; j < Game::BSIZE; ++j) {
            if (board[i][j] == 0) {
                std::pair<int, int> position(i, j);
                empty_tiles.push_back(position);
            }
        }
    }

    int i = rand() % empty_tiles.size(); // Chosing random empty tile
    int p = rand() % 100;
    
    if (p < PROB_NEW_TILE_4) {
        board[empty_tiles[i].first][empty_tiles[i].second] = 4;
    }
    else {
        board[empty_tiles[i].first][empty_tiles[i].second] = 2;
    }
}

bool Game::check_win_status() {
    for (int i = 0; i < BSIZE; ++i) {
        for (int j = 0; j < BSIZE; ++j) {
            if (board[i][j] == WIN_NUMBER) {
                return true;
            }
        }
    }
    
    return false;
}

int Game::get_score() {
    return score;
}

std::ostream & operator<<(std::ostream & out, const Game & game) {
    out << " +===========================+" << std::endl;

    for (int i = 0; i < Game::BSIZE; ++i) {
        for (int j = 0; j < Game::BSIZE; ++j) {
            // setw(4) limits only to 4 digit numbers - theoretical game limit is much higher,
            // but here I assume most of the games played wouldn't be more than 4 digits
            out << " | " << std::setw(4) << game.board[i][j];
        }

        out << " |" << std::endl;
        
        if (i < Game::BSIZE - 1) {
            out << " -----------------------------" << std::endl;
        }
    }
    
    out << " +===========================+" << std::endl;
    out << "Score: " << game.score << std::endl << std::endl;
    out << "Turn " << game.turn << ": ";
    
    return out;
}

