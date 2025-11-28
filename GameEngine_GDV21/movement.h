#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "vector3.h"
#include "gameObject.h"
#include <vector>

Vector3 MovementScript(GameObject player, Vector3 playerPosition);
void npcMovement(GameObject& npc, Vector3& npcPosition, float& npcSpeed);
Vector3 MovementResolve(GameObject& player, Vector3 playerPosition, std::vector<GameObject>& enemies);
#endif
