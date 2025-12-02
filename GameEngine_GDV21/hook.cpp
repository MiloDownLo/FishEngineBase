#include "hook.h"
#include "input.h"
#include "enemy.h"

// Define the hook state variables
bool hookLowering = false;
bool hookGoingUp = false;
float hookLowerSpeed = 0.1f;
float bottomBoundary = -8.0f;
int hookedFishIndex = -1; // -1 means no fish is hooked

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
		hookedFishIndex = -1; // Reset hooked fish
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
					hookedFishIndex = i; // Remember which fish was hooked
					HookEnemy(i); // Mark the fish as hooked
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
				
				// Remove the hooked fish when hook reaches player
				if (hookedFishIndex != -1) {
					RemoveHookedEnemy(hookedFishIndex);
					hookedFishIndex = -1;
				}
			}
		}
	} else {
		// Default position attached to player
		triPos.y = pPos.y + pHalfH - hHalfH + offset;
	}

	triPos.z = pPos.z + 0.01f;

	hook.SetPosition(triPos);
	
	// Draw the fishing line first (so it appears behind the hook)
	DrawFishingLine(hook, player);
	
	hook.DrawTri();
}

void DrawFishingLine(GameObject& hook, GameObject& player)
{
	Vector3 pPos = player.GetPosition();
	Vector3 pScale = player.GetScale();
	
	// Line starts from player's top-right corner
	Vector3 lineStart;
	lineStart.x = pPos.x + (pScale.x * 0.525f);
	lineStart.y = pPos.y + (pScale.y * 0.5f);
	lineStart.z = pPos.z;
	
	// Line ends at hook position
	Vector3 lineEnd = hook.GetPosition();
	
	// Draw white line (1.0, 1.0, 1.0 = white) with width of 2.0f
	GameObject::DrawLine(lineStart, lineEnd, 1.0f, 1.0f, 1.0f, 2.0f);
}

bool IsHookActive()
{
	return hookLowering;
}

int GetHookedFishIndex()
{
	return hookedFishIndex;
}