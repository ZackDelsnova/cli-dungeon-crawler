#pragma once
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "floor.h"
#include "battleSystem.h"
#include "utils.h"
#include "EnemyGenerator.h"

class Game {
    private:
        Player player;
        Floor floor;
        BattleSystem battleSystem;
        EnemyGenerator eneGen;
    
    public:
        Game();
        void run();
        void mainMenu();
        void menu();
        void startNewGame();
        void startBattle();
        void enterRoom(Floor& floor);
        void enemyGen();
        
        std::vector<Enemy> enemies;
};
