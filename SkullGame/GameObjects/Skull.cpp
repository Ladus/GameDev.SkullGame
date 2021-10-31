#pragma once
#include "../Core/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"
#include "Skull.h"

void Skull::Update()
{
	// Local time
	if (LocalTimeUp && LocalTime < LocalTimeMax)
	{
		LocalTime += GetFrameTime();
	}
	else if (!LocalTimeUp && LocalTime > 0)
	{
		LocalTime -= GetFrameTime();
	}
	else
	{
		LocalTimeUp = !LocalTimeUp;
	}

	// Slowly increase speed
	if (Speed < SpeedLimit)
	{
		Speed += SpeedIncrement * GetFrameTime();
	}

	// Oscilate the rotationSpeed
	RotationSpeed = RotationSpeedMax * (LocalTime / LocalTimeMax);

	Vector2 directionLeft = Vector2Rotate(Direction, -RotationSpeed * GetFrameTime());
	Vector2 directionRight = Vector2Rotate(Direction, RotationSpeed * GetFrameTime());

	Vector2 positionRight = Vector2Add(Position, Vector2Scale(directionRight, Speed * Slowdown));
	Vector2 positionLeft = Vector2Add(Position, Vector2Scale(directionLeft, Speed * Slowdown));

	if (Vector2Distance(positionRight, *TargetPosition) < Vector2Distance(positionLeft, *TargetPosition))
	{
		Direction = directionRight;
		Position = positionRight;
	}
	else
	{
		Direction = directionLeft;
		Position = positionLeft;
	}
}

void Skull::Draw()
{
	DrawTextureEx(*SkullTexture, Position, 0, 4, Color{ 255, (unsigned char)Lerp(0, 255, Slowdown),255,255 });
}