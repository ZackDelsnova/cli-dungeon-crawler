#include "Enemy.h"
#include <iostream>

//default constructor
Enemy::Enemy() : name("Enemy"), stats{100.0, 100.0, 10.0, 10.0, 1, 10.0, 100.0} {}

//overloaded constructor
Enemy::Enemy(std::string enemyName, Stats enemyStats, std::string info) 
    : name(enemyName), stats(enemyStats), description(info) {
        scaleByLevel();
    }

void Enemy::scaleByLevel() {
    stats.maxHP = (stats.maxHP * stats.level) / 2;
    stats.hp = stats.maxHP;
    stats.atk = (stats.atk * stats.level) / 2;
    stats.def = (stats.def * stats.level) / 2;
    stats.critChance = (stats.critChance * stats.level) / 2;
    stats.critDmg += stats.critChance > 80.0 ? stats.critChance * 0.5 : 0;
    stats.critChance = stats.critChance > 100.0 ? 100 : stats.critChance;
    int baseReward = stats.level * 10;
    coins = baseReward + (rand() % 11 - 5); // +- 5 varaiation
    exp = static_cast<double>(baseReward + (rand() % 11 - 5)); // same as coins
}

int Enemy::getCoins() const {
    return coins;
}

double Enemy::getEXP() const {
    return exp;
}

void Enemy::displayInfo() const {
    std::cout << "== " << name << " ==\n";
    std::cout << "Description: " << description << "\n\n";
    std::cout << "HP: " << stats.hp << "/" << stats.maxHP << "\n";
    std::cout << "ATK: " << stats.atk << " | DEF: " << stats.def << " | LVL: " << stats.level << "\n";
    std::cout << "Crit%: " << stats.critChance << " | Crit Dmg: " << stats.critDmg << "\n\n";
}

std::string Enemy::getName() const {
    return name;
}

double Enemy::attack() {
    bool isCrit = isCriticalHit();
    double damage = stats.atk * (isCrit ? stats.critDmg/100.0 : 1.0);
    if (isCrit) std::cout << "CRITICAL HIT!\n";
    std::cout << name << " attacks with " << damage << " damage\n";
    return damage; // will use this in battle logic to inflit damage to enemy 
}

double Enemy::getATK() const {
    return stats.atk;
}

double Enemy::getDEF() const {
    return stats.def;
}

void Enemy::defend() {
    isDefending = true;
    std::cout << "Enemy " << name << " braces for impact! DEF is doubled this turn.\n";
}

bool Enemy::getIsDefending() const {
    return isDefending;
}

void Enemy::resetDefense() {
    isDefending = false;
}

double Enemy::getCritChance() const {
    return stats.critChance;
}

double Enemy::getCritDmg() const {
    return stats.critDmg;
}

bool Enemy::isCriticalHit() {
    return (rand() % 100) < stats.critChance;
}

double Enemy::getHP() const {
    return stats.hp;
}

double Enemy::getMaxHP() const {
    return stats.maxHP;
}

void Enemy::setHP(double newHP) {
    if (newHP < 0) newHP = 0;
    if (newHP > stats.maxHP) newHP = stats.maxHP;
    stats.hp = newHP;
}

void Enemy::heal() {
    double healAmount = (0.5 * stats.maxHP);
    setHP(stats.hp + healAmount);
    std::cout << "Enemy " << name << " healed to " << stats.hp << " HP.\n";
}

void Enemy::takeDamage(double dmg) {
    double effectiveDmg = isDefending ? stats.def * 2 : stats.def;
    double actualDamage = dmg - effectiveDmg;

    if (actualDamage < 0) actualDamage = 0;

    stats.hp -= actualDamage;
    if (stats.hp < 0) {
        stats.hp = 0;
        isAlive = false;
    }
    std::cout << "Enemy " << name << " took " << actualDamage << " damage! HP now: " << stats.hp << "\n";
}

bool Enemy::isDead() const {
    return !isAlive;
}

void Enemy::takeTurn(Player& player) {
    if (stats.hp < (0.2 * stats.maxHP) && !hasHealed) {
        heal();
        hasHealed = true;
        return;
    }

    int rng = rand() % 100;

    if (rng < 80) {
        std::cout << "Enemy " << name << " attacks!\n";
        player.takeDamage(stats.atk);
    } else {
        defend();
    }
}
