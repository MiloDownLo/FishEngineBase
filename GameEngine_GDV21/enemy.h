#ifndef ENEMY_H
#define ENEMY_H

#include "vector3.h"
#include "gameObject.h"
#include <vector>

// Enemy variables
extern std::vector<GameObject> enemies;
extern std::vector<float> enemySpeeds;

void InitializeEnemies(int enemyCount, Vector3 formation, float spacing, float colorFactor);
void UpdateEnemies();

#endif