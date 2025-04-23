#include "UI.h"
#include <iostream>
#include <cstdlib>

void UI::clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

int UI::showMainMenu() {
    clearScreen();
    std::cout << "=== Main Menu ===\n";
    std::cout << "1.New Game\n2.Load Game(hasent been impleneted yet)\n3.Exit\n";
    std::cout << "=================\n";
    std::cout << "Enter your choice: ";
    int choice = utils::getValidatedInput(1, 3);
    return choice;
}

int UI::showMenu(const Floor& floor) {
    clearScreen();
    std::cout<< "=== Floor " << floor.getFloorNumber() << " | Room " << floor.getCurrentRoomNumber() + 1 << " ===\n";
    std::cout << "Options: \n";
    std::cout << "0.Main Menu \n1.Player Details \n2.Enter Room \n3.Floor Info\n";
    std::cout << "Enter your action: ";
    int choice = utils::getValidatedInput(0, 3);
    return choice;
}

void UI::displayRoomInfo(const Floor& floor) {
    clearScreen();
    int currentRoom = floor.getCurrentRoomNumber();
    RoomType type = floor.getRoomType(currentRoom);
    std::string desc = floor.getRoomDesc(currentRoom);
    std::cout << "=== Room Information ===\n";
    std::cout << "Room #" << currentRoom + 1 << "\n"; 
    std::cout << "Room Type: ";
    switch (type) {
        case RoomType::Spawner:
            std::cout << "Spawner\n";
            break;
        case RoomType::Rest:
            std::cout << "Rest\n";
            break;
        case RoomType::Trader:
            std::cout << "Trader\n";
            break;
        case RoomType::Elite:
            std::cout << "Elite\n";
            break;
        case RoomType::Boss:
            std::cout << "Boss\n";
            break;
        case RoomType::Chest:
            std::cout << "Treasure Room\n";
            break;
        case RoomType::NextFloor:
            std::cout << "Teleporter to Next Floor";
            break;
        default:
            std::cout << "Unknown\n";
            break;
    }
    std::cout << "\nRoom Description: " << desc << "\n\n";

    goBack();
}

void UI::displayEnemyCount(int count) {
    std::cout << "\nEnemies in this room: " << count << "\n";
}

/*void UI::showEnemyInfo(const BattleSystem& battleSystem) {
    int count = battleSystem.getRemainingEnemies();
    clearScreen();
    displayEnemyCount(count);
    std::cout << "Displaying Currrent Enemy Info\n";
    displayEnemyDetails(battleSystem.getCurrentEnemy());
}*/

void UI::displayMapLayout(const Floor& floor) {
    clearScreen();
    std::cout << "=== Floor " << floor.getFloorNumber() << " Layout === \n\n";

    const auto& rooms = floor.getRooms();
    int currentRoom = floor.getCurrentRoomNumber();
    for (size_t i = 0;i < rooms.size(); ++i) {
        if (i == currentRoom) std::cout << ">>";

        std::cout << "[" << i + 1 << "] ";
        switch (rooms[i].type) {
            case RoomType::Rest: std::cout << "Rest"; break;
            case RoomType::Spawner: std::cout << "Spawner"; break;
            case RoomType::Trader: std::cout << "Trader"; break;
            case RoomType::Elite: std::cout << "Elite"; break;
            case RoomType::Boss: std::cout << "Boss"; break;
            case RoomType::Chest: std::cout << "Chest"; break;
            case RoomType::NextFloor: std::cout << "Next"; break;
        }

        if (i == currentRoom) std::cout << "<<";
        if ( i != rooms.size() -1) std::cout << " -> ";
    }
    std::cout << "\n\n";
    goBack();
}

void UI::displayPlayerDetails(const Player& player) {
    clearScreen();
    player.displayInfo();
    goBack();
}

void UI::displayEnemyDetails(const Enemy& enemy) {
    clearScreen();
    enemy.displayInfo();
    goBack();
}

void UI::goBack() {
    std::cout << "Press enter to go back...";
    std::cin.ignore();
    std::cin.get();
}