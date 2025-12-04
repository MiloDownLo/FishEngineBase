#ifndef ENEMY_H
#define ENEMY_H

#include "vector3.h"
#include "gameObject.h"
#include <vector>

// Enemy variables
extern std::vector<GameObject> enemies;
extern std::vector<float> enemySpeeds;
extern std::vector<bool> enemyHooked;
extern std::vector<Vector3> enemyOriginalPositions;
extern int score;

void InitializeEnemies(int enemyCount, Vector3 formation, float spacing, float colorFactor);
void UpdateEnemies();
void HookEnemy(int enemyIndex);
void UpdateHookedEnemy(int enemyIndex, Vector3 hookPosition);
void RemoveHookedEnemy(int enemyIndex);

#endif