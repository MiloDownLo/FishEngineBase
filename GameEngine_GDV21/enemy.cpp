#include "enemy.h"
#include "movement.h"
#include "iostream"

using namespace std;

// Define enemy variables
vector<GameObject> enemies;
vector<float> enemySpeeds;

void InitializeEnemies(int enemyCount, Vector3 formation, float spacing, float colorFactor)
{
	for (int i = 0; i < enemyCount; i++) {
		GameObject enemy;
		// set the position to have interval for each based on index
		enemy.SetPosition(formation.x + (spacing * i),
						  formation.y + ((spacing / 2) * i),
						  0);
		enemy.SetScale(1, 1, 1);
		enemy.SetColor(1, 0 + (colorFactor * i), 0);
		// Add the enemy instance to the vector collection
		enemies.push_back(enemy);

		// give each NPC its own initial speed (vary sign or magnitude if you want different behaviour)
		float s = 0.05f + (0.005f * i);    // slightly different speeds
		if (i % 2 == 1) s = -s;           // every odd fish goes left first
		enemySpeeds.push_back(s);
	}
}

void UpdateEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		// Make sure to render them every frame
		Vector3 npcPos = enemies[i].GetPosition();
		npcMovement(enemies[i], npcPos, enemySpeeds[i]);
		enemies[i].Draw();
	}
}