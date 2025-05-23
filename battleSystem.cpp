#include "battleSystem.h"
#include <iostream>
#include <chrono>
#include <thread>

BattleSystem::BattleSystem() {
    isBattleOver = false;
}

// Current Battle Status
void BattleSystem::showBattleStatus(const Player& player, const Enemy& enemy) {
    UI::clearScreen();
    UI::displayEnemyCount(enemyList.size());
    std::cout << "Player: " << player.getName() << " | HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
    std::cout << "Enemy: " << enemy.getName() << " | HP: " << enemy.getHP() << "/" << enemy.getMaxHP() << "\n";
}

void BattleSystem::setEnemyList(const std::vector<Enemy>& enemies) {
    enemyList = enemies;
    currentEnemyIndex = 0;
    isBattleOver = false;
}

void BattleSystem::battleAllEnemies(Player& player) {

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (enemyList.empty()) {
        std::cout << "No enemies to fight!\n";
        isBattleOver = true;
        return;
    }
    
    while (currentEnemyIndex < enemyList.size()) {
        startBattle(player);
        if (player.isDead()) {
            std::cout << "Game Over...\n";
            break;
        }

        if (enemyList[currentEnemyIndex].isDead()) {
            currentEnemyIndex++;
        }
    }

    if (!player.isDead()) {
        std::cout << "You have defeated all enemies in the room!\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
    isBattleOver = true;
}

Enemy BattleSystem::getCurrentEnemy() const {
    return enemyList[currentEnemyIndex];
} 

// Main Battle loop
void BattleSystem::startBattle(Player& player) {

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (currentEnemyIndex >= enemyList.size()) {
        std::cout << "No more enemies to fight.\n";
        isBattleOver = true;
        return;
    }

    isBattleOver = false;
    Enemy& enemy = enemyList[currentEnemyIndex];

    UI::displayEnemyDetails(enemy);
    showBattleStatus(player, enemy);

    while (!isBattleOver) {

        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        enemy.decideNextTurn();
        // Player turn
        playerTurn(player, enemy);
        if (enemy.isDead()) {
            handleBattleOutcome(player, enemy);
            break;
        }

        // Enemy turn
        enemyTurn(player, enemy);
        if (player.isDead()) {
            handleBattleOutcome(player, enemy);
            break;
        }
        UI::continueClick();
        showBattleStatus(player, enemy);
    }
}

// Player turn
void BattleSystem::playerTurn(Player& player, Enemy& enemy) {
    bool actionChosen = false;
    do
    {
        UI::clearScreen();
        showBattleStatus(player, enemy);
        std::cout << player.getName() << "'s Turn!" << "\n";
        std::cout << "Action available: \n" 
                  << "1.Attack\n" 
                  << "2.Defend\n"
                  << "3.Heal\n";
        std::cout << "Choose your action: \n"; 
        int choice = utils::getValidatedInput(1, 3);

        switch (choice) {
            case 1: {
                actionChosen = true;
                double dmg = player.attack();
                enemy.takeDamage(dmg);
                break;
            }
            case 2: {
                actionChosen = true;
                player.defend();
                break;
            }
            case 3: {
                actionChosen = true;
                player.heal();
                break;
            }
            default: {
                std::cout << "Invalid Action! You hesitate...\n";
                break;
            }
        }
    } while (!actionChosen);  
}

// Enemy turn
void BattleSystem::enemyTurn(Player& player, Enemy& enemy) {
    std::cout << enemy.getName() << "'s Turn!" << std::endl;
    enemy.takeTurn(player);
}

// Post battle outcome
void BattleSystem::handleBattleOutcome(Player& player, Enemy& enemy) {
    if (enemy.isDead()) {
        std::cout << enemy.getName() << " has been defeated!\n";
        // Award experience points or loot, etc.
        double expGained = enemy.getEXP();
        player.setEXP(expGained);
        int coinsGained = enemy.getCoins();
        player.addCoins(coinsGained);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else if (player.isDead()) {
        std::cout << player.getName() << " has been defeated...\n";
        // Handle player death (e.g., retry battle, game over)
    }
}

bool BattleSystem::isDone() const {
    return currentEnemyIndex >= enemyList.size();
}

bool BattleSystem::getIsBattleOver() const {
    return isBattleOver;
}

int BattleSystem::getRemainingEnemies() const {
    return static_cast<int>(enemyList.size()) - currentEnemyIndex;
}