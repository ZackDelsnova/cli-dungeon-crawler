#pragma once
#include "Player.h"
#include "Enemy.h"
#include "floor.h"
#include "utils.h"
#include "battleSystem.h"

class BattleSystem;

class UI {
    public:
        static int showMainMenu();
        static void clearScreen();
        static int showMenu(const Floor& floor);
        //static void showEnemyInfo(const BattleSystem& BattleSystem);
        static void goBack();
        static void displayEnemyCount(int count);
        static void displayRoomInfo(const Floor& floor);
        static void displayMapLayout(const Floor& floor);
        static void displayPlayerDetails(const Player& player);
        static void displayEnemyDetails(const Enemy& enemy);
};