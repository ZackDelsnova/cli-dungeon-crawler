#pragma once
#include <string>

class Player {
    public:
        struct Stats
        {
            double maxHP;
            double hp;
            double atk;
            double def;
            int level;
            double exp;
            double critChance;
            double critDmg;
        };
        
        Player(); // default constructor
        Player(std::string name); //overloaded constructor

        //generals
        double attack();
        void heal();
        void takeDamage(double dmg);
        void defend();
        void resetDefense();
        void levelUp();
        double requiredEXPToLevel() const;
        void displayInfo() const;
        //void equipWeapon(); not needed for now

        // getter
        std::string getName() const;
        double getHP() const;
        double getMaxHP() const;
        double getATK() const;
        double getDEF() const;
        bool getIsDefending() const;
        double getCritChance() const;
        double getCritDmg() const;
        bool isCriticalHit();
        int getLevel() const;
        double getEXP() const;
        int getCoins() const;
        bool isDead() const;

        // setter
        void setHP(double newHP);
        void decreaseHP(double HP);
        void setEXP(double newEXP);
        void addCoins(int newCoin);
        bool useCoins(int amt);

        //public variables
        std::string name;
        bool isAlive = true;
        Stats stats;
        int coins = 0;
        bool isDefending = false;
};