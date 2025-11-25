#include "../include/GameServer.hpp"
#include <iostream>
#include <chrono>

GameServer::GameServer() {
    Card cards[] = {
        {1, "Fireball", 4, 6, 0},
        {2, "Frostbolt", 3, 3, 0},
        {3, "Shield Block", 3, 0, 5},
        {4, "Fiery War Axe", 3, 3, 2},
        {5, "Mage Armor", 2, 0, 0},
        {6, "Warrior Strike", 2, 3, 0}
    };

    player1.hand = {cards[0], cards[1], cards[4]};
    player2.hand = {cards[2], cards[3], cards[5]};

    player1.maxMana = player1.mana = 3;
    player2.maxMana = player2.mana = 3;
    player1.hasTurn = true;
}

GameServer::~GameServer() { stop(); }

void GameServer::start() {
    if (running_) return;
    running_ = true;
    workerThread_ = std::thread(&GameServer::processCommandQueue, this);
    std::cout << "GAME SERVER STARTED – Ready for battle!\n\n";
}

void GameServer::stop() {
    if (!running_) return;
    { std::lock_guard<std::mutex> lock(mutex_); running_ = false; }
    cv_.notify_all();
    if (workerThread_.joinable()) workerThread_.join();
}

void GameServer::submitCommand(CommandPtr cmd) {
    { std::lock_guard<std::mutex> lock(mutex_); commandQueue_.push(std::move(cmd)); }
    cv_.notify_one();
    std::cout << "Submitted command from Player " << cmd->getPlayerId() << "\n";
}

void GameServer::processCommandQueue() {
    while (running_) {
        CommandPtr cmd;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return !commandQueue_.empty() || !running_; });
            if (!running_) break;
            if (!commandQueue_.empty()) {
                cmd = std::move(commandQueue_.front());
                commandQueue_.pop();
            }
        }
        if (cmd) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            gameState_.apply(std::move(cmd));
            printState();
        }
    }
}