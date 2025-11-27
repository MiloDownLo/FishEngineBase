#include "engine.h"
#include "movement.h"
#include "iostream";

using namespace std;

Vector3 enemyFormation;
Vector3 playerPosition;
float speed = 0;
float spacing = 1.5f;
float scaleFactor = 0.25f;
float colorFactor = 0.1f;
vector<GameObject> enemies;
GameObject player;
int enemyCount = 10;

void Initialize() 
{
	enemyFormation.SetValue(-7.5f, 5, 0);
	for (int i = 0; i < enemyCount; i++) {
		GameObject enemy;
		// set the position to have interval for each based on index
		enemy.SetPosition(enemyFormation.x + (spacing * i), enemyFormation.y, 0);
		enemy.SetScale(1, enemy.GetScale().y - (scaleFactor * i), 1);
		enemy.SetColor(1 - (colorFactor * i), 1, 0);
		// Add the enemy instance to the vector collection
		enemies.push_back(enemy);
	}

	playerPosition.SetValue(0, -5, 0);
	player.SetPosition(playerPosition);
}

void Update() 
{
	Vector3 colliderScale(1, 1, 1);
	player.SetCollider(player.GetPosition(), colliderScale);
	player.DrawSphere(1, 12, 12);

	//TODO: Find a way to compress all this movement stuff into movement.cpp
	Vector3 oldPosition = player.GetPosition();
	Vector3 newPosition = MovementScript(player, oldPosition);
	player.SetPosition(newPosition);
	//TODO: Figure out how to properly unstuck the player on collision
	// though honestly this might not matter if we're using 2d shapes(?)
	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.CheckCollision(enemies[i]))
		{
			player.SetPosition(oldPosition);
			break;
		}
	}
	

	// Iterate through each enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		// Make sure to render them ever frame
		enemies[i].Draw();
		if (player.CheckCollision(enemies[i])) 
		{
			cout << "Collided with enemy at index " << i << endl;
		}
	}
}

int main(int argc, char** argv)
{
	PrepareEngine(argc, argv);
}