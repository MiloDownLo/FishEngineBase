#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector3.h"
#include "color.h"
#include "collider.h"

class GameObject 
{
public:
	GameObject();
	// Setters
	void SetPosition(Vector3 newPosition);
	void SetPosition(float x, float y, float z);
	void SetScale(Vector3 newScale);
	void SetScale(float x, float y, float z);
	void SetRotation(float angle, Vector3 rotation);
	void SetRotation(float angle, float x, float y, float z);
	void SetColor(float red, float green, float blue);
	void SetCollider(Vector3 position, Vector3 scale);
	bool CheckCollision(GameObject other);
	// Option to display a line renderer representing the position/scale of the collider
	//void DrawCollider();
	void SetGradientColor(Vector3 bottom, Vector3 top);

	// Getters
	Vector3 GetScale();
	Vector3 GetPosition();
	Collider GetCollider();

	void DrawCube();
	// Possible modification to this class
	// Add more primitives to this class
	void DrawSphere(float radius, int slices, int stacks);
	void Draw();
	void DrawTri();
	void DrawGradientQuad();
	
	// Static helper to draw a line between two points
	static void DrawLine(Vector3 start, Vector3 end, float red, float green, float blue, float lineWidth = 2.0f);
	//void DrawCube();
	// Create an enum for all possible primitives available in glut and pass in that enum
	//void Draw(Primitives.Cube)

private:
	Vector3 position;
	Vector3 scale;
	// This can be further improved with its own rotation class later on
	Vector3 rotation;
	float angle;
	Color color;
	Collider collider;
	Vector3 gradientTop;
	Vector3 gradientBottom;
};

#endif