#include "engine.h"
#include "movement.h"
#include "hook.h"
#include "enemy.h"
#include "iostream";

using namespace std;

#pragma region Variables
	Vector3 enemyFormation;
	Vector3 playerPosition;
	float speed = 0;
	float spacing = 6.0f;
	float scaleFactor = 0.25f;
	float colorFactor = 0.4f;
	GameObject player;
	GameObject hook;
	GameObject ocean;
	int enemyCount = 3;
#pragma endregion

void Initialize() 
{
	//Initialize enemy variables
	enemyFormation.SetValue(-7.5f, -5, 0);
	InitializeEnemies(enemyCount, enemyFormation, spacing, colorFactor);
	
	//Initialize ocean variables
	ocean.SetPosition(0, -2, -1);
	ocean.SetScale(20, 14, 1);
	//ocean.SetColor(0, 0.54f, 1);
	ocean.SetGradientColor(
		Vector3(0, 0.6f, 1.0f), // top
		Vector3(0, 0.3f, 0.8f) //  bottom
	);

	//Initialize player variables
	playerPosition.SetValue(0, 5, 0);
	player.SetScale(1.6f, 1.1f, 1);
	player.SetColor(0.75f, 0.64f, 0.43f);
	player.SetPosition(playerPosition);

	//Initialize hook variables
	InitializeHook(hook);
}

void Update() 
{
	ocean.DrawGradientQuad();
	
	#pragma region Player Movement and Collision
	if (!IsHookActive()) // Only allow player movement if hook is not active
	{
		// Save current player position
		Vector3 oldPosition = player.GetPosition();

		// Move player and resolve collisions (movement + collision logic moved into movement.cpp)
		Vector3 newPosition = MovementResolve(player, oldPosition, enemies);
		player.SetPosition(newPosition);
	}
	player.Draw();
	#pragma endregion
	
	// Update and draw the hook (now checks for enemy collisions)
	UpdateHook(hook, player, enemies);

	// Update and draw all enemies
	UpdateEnemies();

	// Check for player-enemy collision
	#pragma region Player-Enemy Collision Detection
	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.CheckCollision(enemies[i])) 
		{
			cout << "[!] Clipping through with enemy at index " << i << endl;
		}
	}
	#pragma endregion
}

int main(int argc, char** argv)
{
	PrepareEngine(argc, argv);
}