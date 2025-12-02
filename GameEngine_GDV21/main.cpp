#include "engine.h"
#include "movement.h"
#include "iostream";

using namespace std;

#pragma region Variables
	Vector3 enemyFormation;
	Vector3 playerPosition;
	float speed = 0;
	float spacing = 6.0f;
	float scaleFactor = 0.25f;
	float colorFactor = 0.4f;
	vector<GameObject> enemies;
	vector<float> enemySpeeds;
	GameObject player;
	GameObject hook;
	GameObject ocean;
	int enemyCount = 3;

	// Hook lowering variables
	bool hookLowering = false;
	bool hookGoingUp = false;
	float hookLowerSpeed = 0.1f;
	float bottomBoundary = -8.0f; // Bottom of the screen/ocean
#pragma endregion

void Initialize() 
{
	//Initialize enemy variables
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

	//Initialize hook variables
	hook.SetScale(0.7f, 0.65f, 1); // small triangle
	hook.SetColor(0.4f, 0.4f, 0.4f);
}

void Update() 
{
	ocean.DrawGradientQuad();
	
	#pragma region Player Movement and Collision
	if (!hookLowering) // Only allow player movement if hook is not lowering
	{
		// Save current player position
		Vector3 oldPosition = player.GetPosition();

		// Move player and resolve collisions (movement + collision logic moved into movement.cpp)
		Vector3 newPosition = MovementResolve(player, oldPosition, enemies);
		player.SetPosition(newPosition);
		player.SetPosition(newPosition);
	}
	player.Draw();
	
	#pragma endregion

	// Check for spacebar or E input to start lowering hook
	if ((Input::GetKey(' ') || Input::GetKey('e')) && !hookLowering) 
		{hookLowering = true; hookGoingUp = false;}
	
	// Position and draw the hook
	# pragma region Hook Positioning
		Vector3 pPos = player.GetPosition();
		Vector3 pScale = player.GetScale();
		Vector3 hScale = hook.GetScale();

		float pHalfW = pScale.x * 0.5f;
		float pHalfH = pScale.y * 0.5f;
		float hHalfW = hScale.x * 0.5f;
		float hHalfH = hScale.y * 0.5f;

		// Slight offset so the triangle sits visually on the corner (adjust offset as needed)
		const float offset = 0.4f;

		Vector3 triPos;
		triPos.x = pPos.x + pHalfW - hHalfW + offset;
		
		if (hookLowering) {
			// Get current hook position
			Vector3 currentHookPos = hook.GetPosition();
			
			if (!hookGoingUp) {
				// Move down
				triPos.y = currentHookPos.y - hookLowerSpeed;
				
				// Check if hit bottom boundary
				if (triPos.y <= bottomBoundary) {
					hookGoingUp = true; // Start going back up
				}
			} else {
				// Move back up
				triPos.y = currentHookPos.y + hookLowerSpeed;
				
				// Check if back at player level
				float playerLevel = pPos.y + pHalfH - hHalfH + offset;
				if (triPos.y >= playerLevel) {
					hookLowering = false; // Done with this cast
					hookGoingUp = false;
					triPos.y = playerLevel; // Reset to player position
				}
			}
		}
		else {
			// Default position attached to player
			triPos.y = pPos.y + pHalfH - hHalfH + offset;
		}

		triPos.z = pPos.z + 0.01f; // render slightly in front of the player quad

		hook.SetPosition(triPos);
		hook.DrawTri();
	# pragma endregion

	// Iterate through each enemy
	#pragma region Enemy Movement and Collision
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
	#pragma endregion
}

int main(int argc, char** argv)
{
	PrepareEngine(argc, argv);
}