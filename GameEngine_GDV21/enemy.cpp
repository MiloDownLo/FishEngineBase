#include "enemy.h"
#include "movement.h"
#include "iostream"

using namespace std;

// Define enemy variables
vector<GameObject> enemies;
vector<float> enemySpeeds;
vector<bool> enemyHooked;
vector<Vector3> enemyOriginalPositions;

void InitializeEnemies(int enemyCount, Vector3 formation, float spacing, float colorFactor)
{
	for (int i = 0; i < enemyCount; i++) {
		GameObject enemy;
		// set the position to have interval for each based on index
		Vector3 startPos(formation.x + (spacing * i),
						 formation.y + ((spacing / 2) * i),
						 0);
		enemy.SetPosition(startPos);
		enemy.SetScale(1, 1, 1);
		enemy.SetColor(1, 0 + (colorFactor * i), 0);
		// Add the enemy instance to the vector collection
		enemies.push_back(enemy);
		enemyOriginalPositions.push_back(startPos);
		enemyHooked.push_back(false);

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
		// Only move and draw fish that are not hooked
		if (!enemyHooked[i]) {
			Vector3 npcPos = enemies[i].GetPosition();
			npcMovement(enemies[i], npcPos, enemySpeeds[i]);
			enemies[i].Draw();
		}
	}
}

void HookEnemy(int enemyIndex)
{
	if (enemyIndex >= 0 && enemyIndex < enemyHooked.size()) {
		enemyHooked[enemyIndex] = true;
	}
}

void UpdateHookedEnemy(int enemyIndex, Vector3 hookPosition)
{
	if (enemyIndex >= 0 && enemyIndex < enemies.size() && enemyHooked[enemyIndex]) {
		// Move the fish to the hook position
		enemies[enemyIndex].SetPosition(hookPosition);
		enemies[enemyIndex].Draw();
	}
}

void RemoveHookedEnemy(int enemyIndex)
{
	if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
		// Reset fish to original position and unmark it as hooked
		enemies[enemyIndex].SetPosition(enemyOriginalPositions[enemyIndex]);
		enemyHooked[enemyIndex] = false;
		cout << "Fish caught!" << endl;
	}
}