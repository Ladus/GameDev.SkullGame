#pragma once
#include "../Core/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"

class Skull : public GameObject
{
public:

	Rectangle* Target;
	Texture2D* SkullTexture;

	Rectangle Rect = { 0, 0, 32, 32 };

	float Speed = (float)GetRandomValue(2, 6) / 10;
	float SpeedIncrement = (float)GetRandomValue(1, 10) / 10;
	float SpeedLimit = (float)GetRandomValue(10, 40) / 10;
	float Slowdown = 1; // value from 1 -> 0

	float RotationSpeed = 0;
	float RotationSpeedMax = (float)GetRandomValue(5, 10);

	float LocalTime = (float)GetRandomValue(10, 100) / 10;
	float LocalTimeMax = (float)GetRandomValue(5, 50) / 10;
	bool LocalTimeUp = true;

	Vector2 Direction = { 0, 1 };

	explicit Skull(Rectangle* target, Texture2D* skullTexture)
		: Target(target)
		, SkullTexture(skullTexture)
	{
		int spawnDirection = GetRandomValue(1, 4);
		switch (spawnDirection)
		{
		case 1:
			Rect.x = (float)GetRandomValue(0, GetScreenWidth());
			Rect.y = -8.0f;
			break;
		case 2:
			Rect.x = (float)GetScreenWidth();
			Rect.y = (float)GetRandomValue(0, GetScreenHeight());
			break;
		case 3:
			Rect.x = (float)GetRandomValue(0, GetScreenWidth());
			Rect.y = (float)GetScreenHeight() + 8.0f;
			break;
		case 4:
			Rect.x = -8.0f;
			Rect.y = (float)GetRandomValue(0, GetScreenHeight());
			break;
		default:
			break;
		}
	}

	virtual void Update();

	virtual void Draw();
};
