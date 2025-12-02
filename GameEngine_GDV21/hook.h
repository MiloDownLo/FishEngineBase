#ifndef HOOK_H
#define HOOK_H

#include "vector3.h"
#include "gameObject.h"

// Hook state variables
extern bool hookLowering;
extern bool hookGoingUp;
extern float hookLowerSpeed;
extern float bottomBoundary;

void InitializeHook(GameObject& hook);
void UpdateHook(GameObject& hook, GameObject& player);
bool IsHookActive();

#endif
