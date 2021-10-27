#pragma once
#include "Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Texture2D* ObjectTexture;

	// Position
	Vector2 Position;
	Vector2 MovementDirection;

	float Speed;

	Bullet(Texture2D* objectTexture, Vector2 position, Vector2 direction, float speed)
		: ObjectTexture(objectTexture)
		, Position(position)
		, MovementDirection(direction)
		, Speed(speed)
	{ }

	~Bullet() override = default;

	void Update() override;
	void Draw() override;
};

