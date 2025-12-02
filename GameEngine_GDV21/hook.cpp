#include "hook.h"
#include "input.h"

// Define the hook state variables
bool hookLowering = false;
bool hookGoingUp = false;
float hookLowerSpeed = 0.1f;
float bottomBoundary = -8.0f;

void InitializeHook(GameObject& hook)
{
	hook.SetScale(0.7f, 0.65f, 1);
	hook.SetColor(0.4f, 0.4f, 0.4f);
}

void UpdateHook(GameObject& hook, GameObject& player, std::vector<GameObject>& enemies)
{
	// Check for spacebar or E input to start lowering hook
	if ((Input::GetKey(' ') || Input::GetKey('e')) && !hookLowering) {
		hookLowering = true;
		hookGoingUp = false;
	}

	Vector3 pPos = player.GetPosition();
	Vector3 pScale = player.GetScale();
	Vector3 hScale = hook.GetScale();

	float pHalfW = pScale.x * 0.5f;
	float pHalfH = pScale.y * 0.5f;
	float hHalfW = hScale.x * 0.5f;
	float hHalfH = hScale.y * 0.5f;

	const float offset = 0.4f;

	Vector3 triPos;
	triPos.x = pPos.x + pHalfW - hHalfW + offset;

	if (hookLowering) {
		Vector3 currentHookPos = hook.GetPosition();

		if (!hookGoingUp) {
			// Move down
			triPos.y = currentHookPos.y - hookLowerSpeed;

			// Update hook position temporarily to check collision
			hook.SetPosition(triPos.x, triPos.y, triPos.z);
			hook.SetCollider(hook.GetPosition(), hScale);

			// Check if hook hit any enemy
			bool hitEnemy = false;
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].SetCollider(enemies[i].GetPosition(), enemies[i].GetScale());
				if (hook.CheckCollision(enemies[i])) {
					hitEnemy = true;
					break;
				}
			}

			// Check if hit bottom boundary or an enemy
			if (triPos.y <= bottomBoundary || hitEnemy) {
				hookGoingUp = true;
			}
		} else {
			// Move back up
			triPos.y = currentHookPos.y + hookLowerSpeed;

			// Check if back at player level
			float playerLevel = pPos.y + pHalfH - hHalfH + offset;
			if (triPos.y >= playerLevel) {
				hookLowering = false;
				hookGoingUp = false;
				triPos.y = playerLevel;
			}
		}
	} else {
		// Default position attached to player
		triPos.y = pPos.y + pHalfH - hHalfH + offset;
	}

	triPos.z = pPos.z + 0.01f;

	hook.SetPosition(triPos);
	hook.DrawTri();
}

bool IsHookActive()
{
	return hookLowering;
}