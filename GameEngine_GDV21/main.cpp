#include "engine.h"
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

	if (Input::GetKey('d')) 
	{
		Vector3 rightMovement(0.1f, 0, 0);
		playerPosition += rightMovement;
	}
	if (Input::GetKey('a'))
	{
		Vector3 leftMovement (-0.1f, 0, 0);
		playerPosition += leftMovement;
	}
	if (Input::GetKey('w'))
	{
		Vector3 topMovement(0, 0.1f, 0);
		playerPosition += topMovement;
	}
	if (Input::GetKey('s'))
	{
		Vector3 downMovement(0, -0.1f, 0);
		playerPosition += downMovement;
	}
	player.SetPosition(playerPosition);


	// Iterate through each enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		// Make sure to render them ever frame
		enemies[i].DrawSphere(1, 12, 12);
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