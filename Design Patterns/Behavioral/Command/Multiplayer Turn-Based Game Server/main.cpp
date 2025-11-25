#include <iostream>
#include <chrono>
#include <thread>
#include "GameServer.hpp"
#include "commands/PlayCardCommand.hpp"
#include "commands/AttackCommand.hpp"
#include "commands/EndTurnCommand.hpp"
#include "commands/UseHeroPowerCommand.hpp"
#include "commands/ConcedeCommand.hpp"

int main() {
    std::cout << R"(
╔══════════════════════════════════════════════════════════╗
║    MULTIPLAYER CARD GAME SERVER – COMMAND PATTERN       ║
║          (Like Hearthstone, Marvel Snap, Gwent)         ║
╚══════════════════════════════════════════════════════════╝
)" << std::endl;

    GameServer server;
    server.start();

    std::cout << "Starting epic duel: Alice vs Bob!\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // === TURN 1: Alice ===
    server.submitCommand(std::make_unique<PlayCardCommand>(1, 0));        // Alice plays Fireball
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    server.submitCommand(std::make_unique<PlayCardCommand>(1, 0));        // Alice plays Frostbolt
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    server.submitCommand(std::make_unique<EndTurnCommand>(1));            // End turn

    // === TURN 2: Bob ===
    std::this_thread::sleep_for(std::chrono::seconds(1));
    server.submitCommand(std::make_unique<PlayCardCommand>(2, 0));        // Bob plays Shield Block
    server.submitCommand(std::make_unique<PlayCardCommand>(2, 0));        // Bob plays Fiery War Axe
    server.submitCommand(std::make_unique<UseHeroPowerCommand>(2));      // Bob uses Hero Power
    server.submitCommand(std::make_unique<EndTurnCommand>(2));

    // === TURN 3: Alice fights back ===
    std::this_thread::sleep_for(std::chrono::seconds(1));
    server.submitCommand(std::make_unique<PlayCardCommand>(1, 0));        // Alice plays Mage Armor
    server.submitCommand(std::make_unique<AttackCommand>(1, 0, 0));       // Alice attacks Bob's minion
    server.submitCommand(std::make_unique<EndTurnCommand>(1));

    // === SUDDEN DRAMA: Bob tries to cheat! ===
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nBOB TRIES TO PLAY A CARD WITHOUT MANA (should be blocked!)\n";
    server.submitCommand(std::make_unique<PlayCardCommand>(2, 0));        // Invalid! No mana

    // === ADMIN INTERVENTION: Undo Bob's last valid action ===
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\nADMIN UNDOES BOB'S HERO POWER (anti-grief rollback)\n";
    server.giveGameState().undoLast();  // Direct access for demo (in real game: admin command)

    // === FINAL REPLAY OF ENTIRE MATCH ===
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\nREPLAYING THE ENTIRE MATCH:\n";
    server.replayGame();

    // === GAME OVER ===
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\nSHUTTING DOWN SERVER...\n";
    server.stop();

    std::cout << "\nDemo complete. This is how real game servers work!\n";
    return 0;
}