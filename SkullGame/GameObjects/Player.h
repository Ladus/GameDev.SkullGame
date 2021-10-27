#pragma once
#include "../Core/Debug.h"

#include <list>

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"
#include "Bullet.h"

class Player : public GameObject {
public:
	explicit Player(Texture2D& playerTexture, Texture2D& bulletTexture)
		: PlayerTexture(playerTexture)
		, BulletTexture(bulletTexture) { }

	void Update() override;
	void Draw() override;

	Texture2D PlayerTexture;
	Texture2D BulletTexture;

	// Position
	Vector2 Position = {
		((float)GetScreenWidth() / 2) - ((float)PlayerTexture.width / 2),
		((float)GetScreenHeight() / 2) - ((float)PlayerTexture.height / 2)
	};
	Vector2 MovementDirection = { 0, 0 };

	// Movement speed
	float Speed = 0.0f;
	float MaxSpeed = 200.0f;
	float SpeedIncrement = 500.0f;

	// Aiming and firing
	Vector2 MouseDirection = { 0, 1 };

	std::list<Bullet> BulletList;
};
