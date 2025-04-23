#include "EnemyGenerator.h"
#include <cstdlib>

EnemyGenerator::EnemyGenerator() {
    availableEnemies = {
        //Name, Desc, HP, ATK, DEF, CRIT%, CRIT DMG
        {"Slime", "A translucent squishy creature generally in blue color...", 20.0, 5.0, 5.0, 10.0, 100.0},
        {"Zombie", "A mindless corpse that wants your brain..... if you have one...", 40.0, 10.0, 10.0, 10.0, 100.0},
        {"Skeleton", "A reanimated Bones, that have a bone to pick with you...", 40.0, 10.0, 10.0, 10.0, 100.0}
    };
}

std::vector<EnemyTemplate> EnemyGenerator::getAvailableEnemy() {
    return availableEnemies;
}

std::vector<Enemy> EnemyGenerator::generateEnemies(int floorNumber) {
    std::vector<Enemy> enemies;

    // Scale number of enemies based on floor level. For example:
    // Floor 1–3 = 1–3 enemies, Floor 4–6 = 2–4 enemies, etc.
    int minEnemies = (floorNumber /3) + 1; // At least 1 enemy per floor
    int maxEnemies = minEnemies + 2;    // Max 2 additional enemies per floor
    int numEnemies = rand() % (maxEnemies - minEnemies + 1) + minEnemies; // Random number of enemies

    for (int i = 0; i < numEnemies; ++i) {
        // Scale enemy level based on floor number. For example:
        // Floor 1–3 enemies are level 1–3, Floor 4–6 enemies are level 4–6, etc.
        int level = floorNumber + (rand() % 2); // Scale between floorLevel and floorLevel + 1
        int idx = rand() % availableEnemies.size();

        enemies.push_back(availableEnemies[idx].create(level));
    }

    return enemies;
}