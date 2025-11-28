#include "movement.h"

#include "vector3.h"
#include "gameObject.h"
#include "input.h"

Vector3 MovementScript(GameObject player, Vector3 playerPosition)
{
	if (Input::GetKey('d'))
	{
		Vector3 rightMovement(0.1f, 0, 0);
		playerPosition += rightMovement;
	}
	if (Input::GetKey('a'))
	{
		Vector3 leftMovement(-0.1f, 0, 0);
		playerPosition += leftMovement;
	}
	if (Input::GetKey('s'))
	{
		Vector3 downMovement(0, -0.1f, 0);
		playerPosition += downMovement;
	}

	return (playerPosition);
}