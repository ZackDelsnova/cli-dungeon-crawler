#pragma once
#include "Player.h"
#include <string>

enum class EnemyAction {
    Attack,
    Defend,
    Heal
};

class Enemy {
    public:
        struct Stats
        {
            double maxHP;
            double hp;
            double atk;
            double def;
            int level;
            double critChance;
            double critDmg;
        };

        Enemy(); // default constructr
        Enemy(std::string enemyName, Stats enemyStats, std::string info); // custom constructor
        EnemyAction nextAction;

        // generals
        void scaleByLevel();
        double attack();
        void takeDamage(double dmg);
        void defend();
        void heal();
        void resetDefense();
        void decideNextTurn();
        void takeTurn(Player& player);
        void displayInfo() const;

        //getters
        std::string getName() const;
        int getLevel() const;
        double getHP() const;
        double getMaxHP() const;
        double getATK() const;
        double getDEF() const;
        bool getIsDefending() const;
        double getCritChance() const; 
        double getCritDmg() const;
        bool isCriticalHit();
        bool isDead() const;
        int getCoins() const;
        double getEXP() const;

        //setters
        void setHP(double newHP);
        void decreaseHP(double HP);

        //public variables
        bool isAlive = true;
        bool hasHealed = false;
        bool isDefending = false;
    private:
        std::string name;
        std::string description;
        Stats stats;
        int coins;
        double exp;
};