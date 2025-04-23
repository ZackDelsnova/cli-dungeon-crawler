#pragma once
#include "EnemyTemplate.h"
#include <vector>

class EnemyGenerator {
    private:
        std::vector<EnemyTemplate> availableEnemies;

    public:
        EnemyGenerator();
        std::vector<EnemyTemplate> getAvailableEnemy();
        std::vector<Enemy> generateEnemies(int floorNumber);
};