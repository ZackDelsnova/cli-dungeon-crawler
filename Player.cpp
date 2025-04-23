#include <iostream>
#include "Player.h"

//default constructor
Player::Player() {
    name = "Hero";
    coins = 0;
    stats = {100.0, 100.0, 10.0, 10.0, 1, 0.0, 10.0, 100.0};
}

//overloaded constructor
Player::Player(std::string playerName) {
    name = playerName;
    coins = 0;
    stats = {100.0, 100.0, 10.0, 10.0, 1, 0.0, 10.0, 100.0};
}

void Player::displayInfo() const {
    std::cout << "== " << getName() << " ==\n";
    std::cout << "HP: " << getHP() << "/" << getMaxHP() << "\n";
    std::cout << "ATK: " << getATK() << " | DEF: " << getDEF() << " | LVL: " << getLevel() 
              << "| EXP: " << getEXP() << "/" << requiredEXPToLevel() << "\n";
    std::cout << "Crit%: " << getCritChance() << " | Crit Dmg: " << getCritDmg() << "\n";
    std::cout << "Coins: " << getCoins() << "\n\n";

}

std::string Player::getName() const {
    return name;
}

//EXP setter with auto level-up
void Player::setEXP(double newEXP) {
    stats.exp += newEXP;
    while (stats.exp >= requiredEXPToLevel()) {
        stats.exp -= requiredEXPToLevel();
        levelUp();
    }
}

//EXP requirement formula
double Player::requiredEXPToLevel() const {
    return stats.level * 100 * 1.25;
}

//Level up
void Player::levelUp() {
    stats.level++;
    stats.maxHP += 50;
    stats.hp = getMaxHP();
    stats.atk += 10;
    stats.def += 10;
    stats.critChance += getCritChance() > 100.0 ? 0 : 1;
    stats.critDmg += getCritChance() > 100 ? getCritChance() * 0.25 : 0;
    std::cout << getName() << " leveled up to " << stats.level << "!\n";
}

bool Player::isCriticalHit() {
    return (rand() % 100) < stats.critChance;
}

//action methods
double Player::attack() {
    bool isCrit = isCriticalHit();
    double damage = getATK() * (isCrit ? getCritDmg()/100.0 : 1.0);
    if (isCrit) std::cout << "CRITICAL HIT!\n";
    std::cout << getName() << " attacks with " << damage << " damage\n";
    return damage; // will use this in battle logic to inflit damage to enemy 
}

void Player::defend() {
    isDefending = true;
    std::cout << getName() << " braces for impact! DEF is doubled this turn.\n";
}

bool Player::getIsDefending() const {
    return isDefending; 
}

void Player::resetDefense() {
    isDefending = false;
}

double Player::getHP() const {
    return stats.hp;
}

double Player::getMaxHP() const {
    return stats.maxHP;
}

double Player::getATK() const {
    return stats.atk;
}

double Player::getDEF() const {
    return stats.def;
}

double Player::getCritChance() const {
    return stats.critChance;
}

double Player::getCritDmg() const {
    return stats.critDmg;
}

double Player::getEXP() const {
    return stats.exp;
}

int Player::getLevel() const {
    return stats.level;
}

int Player::getCoins() const {
    return coins;
}

// logic to add coin when defeating enemy
void Player::addCoins(int newCoin) {
    if (newCoin < 0) newCoin = 0;
    coins += newCoin;
}

// logic to use coin in trader
bool Player::useCoins(int amt) {
    if (amt > coins) {
        std::cout << "Not enough coins!\n";
        return false; // in trader to say not enough coins
    } else {
        coins -= amt;
        return true; // in trader to say purchase succesful
    }
}

void Player::setHP(double newHP) {
    if (newHP <= 0) {
        newHP = 0;
        isAlive = false;
    } 
    if (newHP > stats.maxHP) newHP = stats.maxHP;
    stats.hp = newHP;
}

void Player::decreaseHP(double hpDecrease) {
    stats.hp -= hpDecrease;
    if (stats.hp <= 0) {
        setHP(0);
    }
}

void Player::takeDamage(double dmg) {
    double effectiveDef = isDefending ? stats.def * 2 : stats.def;
    double actualDamage = dmg - effectiveDef;

    if (actualDamage <= 0) actualDamage = 0;
    
    decreaseHP(actualDamage);

    std::cout << getName() << " took " << actualDamage << " damage! HP now: " << stats.hp << "\n";
}

//check in battle logic
bool Player::isDead() const {
    return !isAlive;
}

void Player::heal() {
    double healAmount = 0.2 * stats.maxHP;
    setHP(stats.hp + healAmount);
    std::cout << getName() << " healed to " << stats.hp << " HP.\n";
}
