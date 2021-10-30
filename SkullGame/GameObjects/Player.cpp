#include "../Core/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "../Core/GameObject.h"
#include "Player.h"

void Player::Update() {
	// Keyboard movement
	MovementDirection = { 0, 0 };
	if (IsKeyDown(KEY_W)) {
		MovementDirection = Vector2Add(MovementDirection, { 0, -1 });
	}
	if (IsKeyDown(KEY_D)) {
		MovementDirection = Vector2Add(MovementDirection, { 1, 0 });
	}
	if (IsKeyDown(KEY_S)) {
		MovementDirection = Vector2Add(MovementDirection, { 0, 1 });
	}
	if (IsKeyDown(KEY_A)) {
		MovementDirection = Vector2Add(MovementDirection, { -1, 0 });
	}

	if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) && Speed < MaxSpeed) {
		Speed += SpeedIncrement * GetFrameTime();
	}
	else if (!(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) && Speed > 0) {
		Speed -= (SpeedIncrement * GetFrameTime());
	}

	// Update Position
	Position = Vector2Add(Position, Vector2Multiply(Vector2Multiply(MovementDirection, { Speed, Speed }), { GetFrameTime(), GetFrameTime() }));

	// Add bullet to SkullGame bullet list
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 targetVector = Vector2Subtract(GetMousePosition(), Position);
		targetVector = Vector2Normalize(targetVector);
		targetVector = Vector2Add(targetVector, Vector2{ (float) GetRandomValue(-100,100) / 700, (float)GetRandomValue(-100,100) / 1000 });

		m_BulletList.emplace_back(&BulletTexture, Vector2{ Position.x + 8, Position.y + 8 }, targetVector, (float)GetRandomValue(500, 820));
	}
}

void Player::Draw() {
	DrawTextureEx(PlayerTexture, Position, 0, 4, WHITE);

#ifdef DEBUG
	DrawText(TextFormat("Debug: bullets %i ", m_BulletList.size()), 20, GetScreenHeight() - 50, 20, BLACK);
#endif // DEBUG

}
