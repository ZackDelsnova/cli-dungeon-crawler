#pragma once
#include "Enemy.h"
#include <string>

struct EnemyTemplate {
    std::string name;
    std::string description;
    double baseHP;
    double baseATK;
    double baseDEF;
    double baseCritChance;
    double baseCritDmg;

    Enemy create(int level) {
        Enemy::Stats s;
        s.level = level;
        s.maxHP = baseHP;
        s.hp = baseHP;
        s.atk = baseATK;
        s.def = baseDEF;
        s.critChance = baseCritChance;
        s.critDmg = baseCritDmg;

        Enemy e(name, s, description);

        e.scaleByLevel();

        return e;
    }
};