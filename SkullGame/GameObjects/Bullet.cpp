#include "../Core/Debug.h"
#include "Bullet.h"

void Bullet::Update() {

	float deltaSpeed = Speed * GetFrameTime();
	auto V2DeltaSpeed = Vector2{ deltaSpeed, deltaSpeed };

	Vector2 Displacement = Vector2Multiply(MovementDirection, V2DeltaSpeed);

	Position = Vector2Add(Position, Displacement);
}

void Bullet::Draw() {
	DrawTextureEx(*ObjectTexture, Position, 0, 2, WHITE);

#ifdef DEBUG
	auto text1 = TextFormat("Direction: %f %f", MovementDirection.x, MovementDirection.y);
	DrawRectangle(300, 200, MeasureText(text1, 10), 10, BLACK);
	DrawText(text1, 300, 200, 10, WHITE);

	auto text2 = TextFormat("Position: %f %f", Position.x, Position.y);
	DrawRectangle(300, 220, MeasureText(text2, 10), 10, BLACK);
	DrawText(text2, 300, 220, 10, WHITE);
#endif // DEBUG
}