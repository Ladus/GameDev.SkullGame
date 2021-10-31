#pragma once
#include "../Core/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"

class Bullet : public GameObject
{
public:
	Texture2D* ObjectTexture;

	// Position
	Rectangle Rect = { 0, 0, 16, 16 };
	Vector2 MovementDirection;

	float Speed;

	Bullet(Texture2D* objectTexture, Rectangle rect, Vector2 direction, float speed)
		: ObjectTexture(objectTexture)
		, Rect(rect)
		, MovementDirection(direction)
		, Speed(speed)
	{
	}

	~Bullet() override = default;

	void Update() override;
	void Draw() override;
};

