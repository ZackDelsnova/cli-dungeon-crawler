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
    stats.maxHP = (getMaxHP() * getLevel()) / 2;
    stats.hp = getMaxHP();
    stats.atk = (getATK() * getLevel()) / 2;
    stats.def = (getDEF() * getLevel()) / 2;
    stats.critChance = (getCritChance() * getLevel()) / 2;
    stats.critDmg += getCritChance() > 80.0 ? getCritChance() * 0.5 : 0;
    stats.critChance = getCritChance() > 100.0 ? 100 : getCritChance();
    int baseReward = getLevel() * 10;
    coins = baseReward + (rand() % 11 - 5); // +- 5 varaiation
    exp = static_cast<double>(baseReward + (rand() % 11 - 5)); // same as coins
    isAlive = true;
    hasHealed = false;
}

int Enemy::getLevel() const {
    return stats.level;
}

int Enemy::getCoins() const {
    return coins;
}

double Enemy::getEXP() const {
    return exp;
}

void Enemy::displayInfo() const {
    std::cout << "== " << getName() << " ==\n";
    std::cout << "Description: " << description << "\n\n";
    std::cout << "HP: " << getHP() << "/" << getMaxHP() << "\n";
    std::cout << "ATK: " << getATK() << " | DEF: " << getDEF() << " | LVL: " << getLevel() << "\n";
    std::cout << "Crit%: " << getCritChance() << " | Crit Dmg: " << getCritDmg() << "\n\n";
}

std::string Enemy::getName() const {
    return name;
}

double Enemy::attack() {
    bool isCrit = isCriticalHit();
    double damage = getATK() * (isCrit ? getCritDmg()/100.0 : 1.0);
    if (isCrit) std::cout << "CRITICAL HIT!\n";
    std::cout << getName() << " attacks with " << damage << " damage\n";
    return damage; // will use this in battle logic to inflict damage to enemy 
}

double Enemy::getATK() const {
    return stats.atk;
}

double Enemy::getDEF() const {
    return stats.def;
}

void Enemy::defend() {
    isDefending = true;
    std::cout << "Enemy " << getName() << " braces for impact! DEF is doubled this turn.\n";
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
    if (newHP <= 0) {
        newHP = 0;
        isAlive = false;
    } 
    if (newHP > stats.maxHP) newHP = stats.maxHP;
    stats.hp = newHP;
}

void Enemy::heal() {
    double healAmount = (0.5 * stats.maxHP);
    setHP(stats.hp + healAmount);
    std::cout << "Enemy " << name << " healed to " << stats.hp << " HP.\n";
}

void Enemy::decreaseHP(double hpDecrease) {
    stats.hp -= hpDecrease;
    if (stats.hp <= 0) {
        setHP(0);
    }
}

void Enemy::takeDamage(double dmg) {
    double effectiveDmg = isDefending ? getDEF() * 2 : getDEF();
    double actualDamage = dmg - effectiveDmg;

    if (actualDamage <= 0) actualDamage = 0;

    decreaseHP(actualDamage);

    std::cout << "Enemy " << getName() << " took " << actualDamage << " damage! HP now: " << getHP() << "\n";
}

bool Enemy::isDead() const {
    return !isAlive;
}

void Enemy::decideNextTurn() {
    isDefending = false;

    if (getHP() < (0.2 * getMaxHP()) && !hasHealed) {
        nextAction = EnemyAction::Heal;
        return;
    }

    int rng = rand() % 100;

    if (rng < 80) {
        nextAction = EnemyAction::Attack;
    } else {
        nextAction = EnemyAction::Defend;
        defend();
    }
}

void Enemy::takeTurn(Player& player) {
    switch (nextAction) {
        case EnemyAction::Attack: 
            std::cout << "Enemy " << getName() << " attacks!\n";
            player.takeDamage(attack());
            break;
        case EnemyAction::Heal:
            heal();
            hasHealed = true;
            break;
        case EnemyAction::Defend:
            resetDefense();
            break;
    }
}
