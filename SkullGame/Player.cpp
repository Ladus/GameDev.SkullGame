#include "Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "GameObject.h"
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

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

		Vector2 targetVector = Vector2Subtract(GetMousePosition(), Position);
		targetVector = Vector2Normalize(targetVector);

		BulletList.emplace_back(BulletTexture, Vector2 {Position.x + 8, Position.y + 8}, targetVector, (float)GetRandomValue(500, 820));
	}

	// Update all bullets
	for (auto &bullet : BulletList) {
		bullet.Update();

		if (bullet.Position.x < -20
			|| bullet.Position.x > (float)GetScreenWidth() + 20
			|| bullet.Position.y < -20
			|| bullet.Position.y > (float)GetScreenHeight() + 20) {
			// TODO: Remove bullets that are off screen
		}
	}

}

void Player::Draw() {
	DrawTextureEx(*PlayerTexture, Position, 0, 4, WHITE);

	// Draw all bullets
	for (auto &bullet : BulletList) {
		bullet.Draw();
	}

#ifdef DEBUG
	DrawText(TextFormat("Debug: bullets %i ", BulletList.size()), 20, GetScreenHeight() - 50, 20, BLACK);
#endif // DEBUG

}
