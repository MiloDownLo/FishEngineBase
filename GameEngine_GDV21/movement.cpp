#include "movement.h"

#include "vector3.h"
#include "gameObject.h"
#include "input.h"

Vector3 MovementScript(GameObject player, Vector3 playerPosition)
{
	// Define movement boundaries (walls on both sides)
	float leftWall = -8.0f;   // Left boundary
	float rightWall = 8.0f;   // Right boundary
	
	if (Input::GetKey('d'))
	{
		Vector3 rightMovement(0.1f, 0, 0);
		Vector3 newPosition = playerPosition + rightMovement;
		
		// Only move right if not hitting the right wall
		if (newPosition.x <= rightWall)
		{
			playerPosition = newPosition;
		}
	}
	if (Input::GetKey('a'))
	{
		Vector3 leftMovement(-0.1f, 0, 0);
		Vector3 newPosition = playerPosition + leftMovement;
		
		// Only move left if not hitting the left wall
		if (newPosition.x >= leftWall)
		{
			playerPosition = newPosition;
		}
	}
	if (Input::GetKey('s'))
	{
		Vector3 downMovement(0, -0.1f, 0);
		playerPosition += downMovement;
	}

	return (playerPosition);
}