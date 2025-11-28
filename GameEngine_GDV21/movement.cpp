#include "movement.h"

#include "vector3.h"
#include "gameObject.h"
#include "input.h"

// Define movement boundaries (walls on both sides)
float leftWall = -8.0f;   // Left boundary
float rightWall = 8.0f;   // Right boundary

Vector3 MovementScript(GameObject player, Vector3 playerPosition)
{
	float moveSpeed = 0.1f;

	// Horizontal movement
	if (Input::GetKey('d'))
	{
		Vector3 rightMovement(0.1f, 0, 0);
		Vector3 newPosition = playerPosition + rightMovement;
		
		// Only move right if not hitting the right wall
		if (newPosition.x <= rightWall)
			{playerPosition.x += moveSpeed;}
	}

	if (Input::GetKey('a'))
	{
		Vector3 leftMovement(-0.1f, 0, 0);
		Vector3 newPosition = playerPosition + leftMovement;
		
		// Only move left if not hitting the left wall
		if (newPosition.x >= leftWall)
			{playerPosition.x -= moveSpeed;}
	}

	// Vertical movement (FOR TESTING PURPOSES ONLY)
	/*
	if (Input::GetKey('s'))
		{playerPosition.y -= moveSpeed;}
	if (Input::GetKey('w'))
		{playerPosition.y += moveSpeed;}
	*/

	return (playerPosition);
}

// Simple NPC movement logic (move left/right between boundaries)
void npcMovement(GameObject& npc, Vector3& npcPosition, float& npcSpeed)
{
	if (npcPosition.x >= rightWall || npcPosition.x <= leftWall)
	{
		npcSpeed = -npcSpeed; // flip direction for this specific NPC
	}

	npcPosition.x += npcSpeed;
	npc.SetPosition(npcPosition);
}


// Resolve player movement and collisions and return the final position.
// Uses axis-separated resolution: move X then Y and revert only the axis that collides.
Vector3 MovementResolve(GameObject& player, Vector3 playerPosition, std::vector<GameObject>& enemies)
{
	// Keep enemy colliders up-to-date for collision tests
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].SetCollider(enemies[i].GetPosition(), enemies[i].GetScale());
	}

	Vector3 oldPosition = playerPosition;
	Vector3 targetPosition = MovementScript(player, oldPosition);

	// Use player's scale for collider size
	Vector3 playerColliderScale = player.GetScale();

	Vector3 resolved = oldPosition;

	// Move on X, test collisions, revert X if needed
	resolved.x = targetPosition.x;
	player.SetPosition(resolved);
	player.SetCollider(player.GetPosition(), playerColliderScale);

	bool collided = false;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.CheckCollision(enemies[i]))
		{
			collided = true;
			break;
		}
	}
	if (collided)
	{
		resolved.x = oldPosition.x;
		player.SetPosition(resolved);
		player.SetCollider(player.GetPosition(), playerColliderScale);
	}

	// Move on Y, test collisions, revert Y if needed
	resolved.y = targetPosition.y;
	player.SetPosition(resolved);
	player.SetCollider(player.GetPosition(), playerColliderScale);

	collided = false;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (player.CheckCollision(enemies[i]))
		{
			collided = true;
			break;
		}
	}
	if (collided)
	{
		resolved.y = oldPosition.y;
		player.SetPosition(resolved);
		player.SetCollider(player.GetPosition(), playerColliderScale);
	}

	// Return the final resolved position (Z doesn't matter for our purposes, it's 2D)
	return resolved;
}