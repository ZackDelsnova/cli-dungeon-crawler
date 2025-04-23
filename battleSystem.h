#pragma once
#include "UI.h"
#include "floor.h"
#include "Player.h"
#include "Enemy.h"
#include "utils.h"
#include <vector>

class BattleSystem {
    public:
        BattleSystem();
        
        void showBattleStatus(const Player& player, const Enemy& enemy);
        void startBattle(Player& player);
        void setEnemyList(const std::vector<Enemy>& enemies);
        void battleAllEnemies(Player& player);
        bool getIsBattleOver() const;
        int getRemainingEnemies() const;
        bool isDone() const;
        Enemy getCurrentEnemy() const;

    private:
        bool isBattleOver; 
        std::vector<Enemy> enemyList; //enemy list generated from EnemyGenerator
        int currentEnemyIndex = 0;
        void playerTurn(Player& player, Enemy& enemy);
        void enemyTurn(Player& player, Enemy& enemy);
        void handleBattleOutcome(Player& player, Enemy& enemy);
};