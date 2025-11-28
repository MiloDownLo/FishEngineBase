#include "engine.h"
#include "movement.h"
#include "iostream";

using namespace std;

Vector3 enemyFormation;
Vector3 playerPosition;
float speed = 0;
float spacing = 6.0f;
float scaleFactor = 0.25f;
float colorFactor = 0.1f;
vector<GameObject> enemies;
GameObject player;
int enemyCount = 3;

void Initialize() 
{
	enemyFormation.SetValue(-7.5f, -5, 0);
	for (int i = 0; i < enemyCount; i++) {
		GameObject enemy;
		// set the position to have interval for each based on index
		enemy.SetPosition(enemyFormation.x + (spacing * i),
						  enemyFormation.y + ((spacing/2) * i),
						  0);
		enemy.SetScale(1, 1, 1);
		enemy.SetColor(1 - (colorFactor * i), 1, 0);
		// Add the enemy instance to the vector collection
		enemies.push_back(enemy);
	}

	//Initialize player variables
	playerPosition.SetValue(0, 5, 0);
	player.SetScale(1.5f, 1, 1);
	player.SetColor(0.75f, 0.64f, 0.43f);
	player.SetPosition(playerPosition);
}

void Update() 
{
	// Save current player position
	Vector3 oldPosition = player.GetPosition();

	// Move player and resolve collisions (movement + collision logic moved into movement.cpp)
	Vector3 newPosition = MovementResolve(player, oldPosition, enemies);
	player.SetPosition(newPosition);

	// Draw player at resolved position
	player.SetPosition(newPosition);

	//player.DrawSphere(1, 12, 12);
	player.Draw();
	

	// Iterate through each enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		// Make sure to render them every frame
		enemies[i].Draw();
		if (player.CheckCollision(enemies[i])) 
		{
			cout << "[!] Clipping through with enemy at index " << i << endl;
		}
	}
}

int main(int argc, char** argv)
{
	PrepareEngine(argc, argv);
}