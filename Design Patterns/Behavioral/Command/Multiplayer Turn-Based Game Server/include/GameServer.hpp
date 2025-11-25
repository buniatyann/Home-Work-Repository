#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "GameState.hpp"
#include "Command.hpp"
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

class GameServer {
public:
    GameServer();
    ~GameServer();

    void start();
    void stop();
    void submitCommand(CommandPtr cmd);

    void printState() const { gameState_.print(); }
    void replayGame() const { gameState_.replay(); }

    GameState giveGameState() const {
        return gameState_;
    }

private:
    void processCommandQueue();

    GameState gameState_;
    std::queue<CommandPtr> commandQueue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::thread workerThread_;
    bool running_ = false;
};

#endif // GAME_SERVER_HPP