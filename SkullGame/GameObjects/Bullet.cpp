#include "../Core/Debug.h"
#include "Bullet.h"

void Bullet::Update()
{

	float deltaSpeed = Speed * GetFrameTime();
	auto V2DeltaSpeed = Vector2{ deltaSpeed, deltaSpeed };

	Vector2 Displacement = Vector2Multiply(MovementDirection, V2DeltaSpeed);

	Position = Vector2Add(Position, Displacement);
}

void Bullet::Draw()
{
	DrawTextureEx(*ObjectTexture, Position, 0, 2, WHITE);
}