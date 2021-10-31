#include "../Core/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"
#include "Player.h"

void Player::Update()
{
	// Keyboard movement
	MovementDirection = { 0, 0 };
	if (IsKeyDown(KEY_W))
	{
		MovementDirection = Vector2Add(MovementDirection, { 0, -1 });
	}
	if (IsKeyDown(KEY_D))
	{
		MovementDirection = Vector2Add(MovementDirection, { 1, 0 });
	}
	if (IsKeyDown(KEY_S))
	{
		MovementDirection = Vector2Add(MovementDirection, { 0, 1 });
	}
	if (IsKeyDown(KEY_A))
	{
		MovementDirection = Vector2Add(MovementDirection, { -1, 0 });
	}

	if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) && Speed < MaxSpeed)
	{
		Speed += SpeedIncrement * GetFrameTime();
	}
	else if (!(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) && Speed > 0)
	{
		Speed -= (SpeedIncrement * GetFrameTime());
	}

	// Update Position
	Vector2 position = Vector2Add(
		{ Rect.x, Rect.y },
		Vector2Multiply(
			Vector2Multiply(MovementDirection, { Speed, Speed }),
			{ GetFrameTime(), GetFrameTime() }
		)
	);

	Rect.x = position.x;
	Rect.y = position.y;

	// Add bullet to SkullGame bullet list
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 targetVector = Vector2Subtract(GetMousePosition(), { Rect.x, Rect.y });
		targetVector = Vector2Normalize(targetVector);

		Vector2 randomTargetVector = { 0.0f, 0.0f };

		int amountOfBullets = (int) (GetFrameTime() * 100);
		for (int x = 0; x < amountOfBullets; x++)
		{
			randomTargetVector = Vector2Add(targetVector, Vector2{ (float)GetRandomValue(-100,100) / 700, (float)GetRandomValue(-100,100) / 1000 });
			m_BulletList.emplace_back(
				&BulletTexture, 
				Rectangle { Rect.x + (Rect.width/2), Rect.y + (Rect.height / 2), 0.0f, 0.0f}, 
				randomTargetVector, 
				(float)GetRandomValue(500, 820));
		}
	}
}

void Player::Draw()
{
	DrawTextureEx(PlayerTexture, { Rect.x, Rect.y }, 0, TextureScale, WHITE);
}