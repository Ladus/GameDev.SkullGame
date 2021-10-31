#include "../Core/Debug.h"
#include "Bullet.h"

void Bullet::Update()
{

	float deltaSpeed = Speed * GetFrameTime();
	auto V2DeltaSpeed = Vector2{ deltaSpeed, deltaSpeed };

	Vector2 Displacement = Vector2Multiply(MovementDirection, V2DeltaSpeed);

	Vector2 position = Vector2Add({ Rect.x, Rect.y }, Displacement);
	Rect.x = position.x;
	Rect.y = position.y;
}

void Bullet::Draw()
{
	DrawTextureEx(*ObjectTexture, { Rect.x, Rect.y }, 0, 2, WHITE);
}