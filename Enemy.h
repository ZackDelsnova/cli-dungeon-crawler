#pragma once
#include "Player.h"
#include <string>

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

        // generals
        void scaleByLevel();
        double attack();
        void takeDamage(double dmg); //done
        void defend(); //done
        void heal(); //done
        void resetDefense(); //done
        void takeTurn(Player& player); //done
        void displayInfo() const; //done

        //getters
        std::string getName() const; //done
        double getHP() const; //done
        double getMaxHP() const; //done
        double getATK() const;
        double getDEF() const;
        bool getIsDefending() const; //done
        double getCritChance() const; 
        double getCritDmg() const;
        bool isCriticalHit();
        bool isDead() const;
        int getCoins() const;
        double getEXP() const;

        //setters
        void setHP(double newHP); //done

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