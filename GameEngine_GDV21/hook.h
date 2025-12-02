#ifndef HOOK_H
#define HOOK_H

#include "vector3.h"
#include "gameObject.h"
#include <vector>

// Hook state variables
extern bool hookLowering;
extern bool hookGoingUp;
extern float hookLowerSpeed;
extern float bottomBoundary;

void InitializeHook(GameObject& hook);
void UpdateHook(GameObject& hook, GameObject& player, std::vector<GameObject>& enemies);
bool IsHookActive();

#endif
