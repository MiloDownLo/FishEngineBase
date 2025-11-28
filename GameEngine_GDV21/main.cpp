#include "engine.h"
#include "movement.h"
#include "iostream";

using namespace std;

Vector3 enemyFormation;
Vector3 playerPosition;
float speed = 0;
float spacing = 6.0f;
float scaleFactor = 0.25f;
float colorFactor = 0.4f;
vector<GameObject> enemies;
vector<float> enemySpeeds;
GameObject player;
GameObject ocean;
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
		enemy.SetColor(1, 0 + (colorFactor * i), 0);
		// Add the enemy instance to the vector collection
		enemies.push_back(enemy);

		// give each NPC its own initial speed (vary sign or magnitude if you want different behaviour)
		float s = 0.05f + (0.005f * i);    // slightly different speeds
		if (i % 2 == 1) s = -s;           // every odd fish goes left first
		enemySpeeds.push_back(s);
	}
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
}

void Update() 
{
	ocean.DrawGradientQuad();
	
	// Save current player position
	Vector3 oldPosition = player.GetPosition();

	// Move player and resolve collisions (movement + collision logic moved into movement.cpp)
	Vector3 newPosition = MovementResolve(player, oldPosition, enemies);
	player.SetPosition(newPosition);
	player.SetPosition(newPosition);

	//player.DrawSphere(1, 12, 12);
	player.Draw();
	

	// Iterate through each enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		// Make sure to render them every frame
		Vector3 npcPos = enemies[i].GetPosition();
		npcMovement(enemies[i], npcPos, enemySpeeds[i]);
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