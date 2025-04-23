#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include "game.h"

Game::Game() : floor(1) { }

void Game::run()
{
    // seed randomness
    srand(static_cast<unsigned int>(time(nullptr)));
  
    mainMenu();
}

void Game::mainMenu() {
    bool isMainMenu = true;
    while (isMainMenu) {
        UI::clearScreen();
        int choice = UI::showMainMenu();
    
        switch (choice) {
            case 1:
                UI::clearScreen();
                std::cout << "Starting new game...\n";
                isMainMenu = false;
                startNewGame();
                break;
            case 2:
                UI::clearScreen();
                std::cout << "Load game not implemented.\n";
                isMainMenu = false;
                break;
            case 3:
                std::cout << "Exiting...\n";
                isMainMenu = false;
                exit(0);
                break;
            default:
                UI::clearScreen();
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}

void Game::menu() {
    bool inMenu = true;
    while (inMenu) {
        int choice = UI::showMenu(floor);

        switch (choice) {
            case 0:
                inMenu = false;
                mainMenu();
                break; 
            case 1:
                std::cout << "Showing player details...\n";
                UI::displayPlayerDetails(player);
                break;
            case 2:
                std::cout << "Entering room...\n";
                enterRoom(floor);
                break;
            case 3:
                std::cout << "Showing floor info...\n";
                UI::displayMapLayout(floor);
                break;
            default:
                std::cout << "Invalid Choice!\n";
                break;
        }
    }
}

void Game::startNewGame() {
    std::string name;
    do {
        UI::clearScreen();
        std::cout << "Enter Player name (max 20 characters): ";
        std::getline(std::cin >> std::ws, name);

        if(name.empty() || name.length() > 20 || std::all_of(name.begin(), name.end(), isspace)) {
            std::cout << "Invalid name. Try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else {
            break;
        }
    } while (true);
    name = utils::formatName(name);
    player = Player(name);
    menu();
}

void Game::enterRoom(Floor& floor) {
    const Room& currentRoom = floor.getCurrentRoom();

    if(currentRoom.type == RoomType::Spawner /* || 
       currentRoom.type == RoomType::Boss ||
       currentRoom.type == RoomType::Elite */) {
        enemyGen();
    }

    bool inRoom = true;
    while (inRoom)
    {
        UI::clearScreen();
        std::cout << "=== Floor " << floor.getFloorNumber() << " | Room " << floor.getCurrentRoomNumber() + 1 << " ===\n";
        std::cout << "Actions available: \n";
        std::cout << "1.Go Back\n";
        std::cout << "2.Room Information\n";
        if (currentRoom.type == RoomType::Spawner /*|| 
            currentRoom.type == RoomType::Elite || 
            currentRoom.type == RoomType::Boss */) 
        {
            std::cout << "3.Enter Battle\n";
        }
        std::cout << "4.Next Room\n";
        std::cout << "Enter your action: ";
        int choice = utils::getValidatedInput(1, 4);

        if (choice == 4 && !currentRoom.isRoomCompleted) {
            std::cout << "Room not completed. Defeat all enemies first!\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            continue; 
        } 

        switch (choice) {
            case 1:
                inRoom = false;
                menu();
                break;
            case 2:
                UI::displayRoomInfo(floor);
                break;
            case 3:
            if (currentRoom.type == RoomType::Spawner /* || 
                currentRoom.type == RoomType::Elite || 
                currentRoom.type == RoomType::Boss */) 
            {
                startBattle();
            } else {
                std::cout << "No battle in this room, room is either safe or Work in Progress\n";
            }
            break;
            case 4:
                std::cout << "Moving to next room";
                floor.moveForward();
                inRoom = false;
                break;
            default:
                std::cout << "Invalid action!\n";
                break;
        }
    }
}

void Game::enemyGen() {
    int floorNum = floor.getFloorNumber();
    battleSystem.setEnemyList(eneGen.generateEnemies(floorNum));
}

void Game::startBattle() {
    UI::clearScreen();
    
    while (!battleSystem.isDone()) {
        battleSystem.battleAllEnemies(player);
    }

    //chk if battle is over and all enemies are killed
    //if yes set is Room completed to true
    if (battleSystem.getIsBattleOver() && battleSystem.isDone()) {
        floor.setRoomComplete(); //just doing room[currentRoom].isCompleted = true
    }
}
