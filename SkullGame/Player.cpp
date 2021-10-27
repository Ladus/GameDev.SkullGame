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
		targetVector = Vector2Add(targetVector, Vector2{ (float) GetRandomValue(-100,100) / 1000, (float)GetRandomValue(-100,100) / 1000 });

		BulletList.emplace_back(&BulletTexture, Vector2{ Position.x + 8, Position.y + 8 }, targetVector, (float)GetRandomValue(500, 820));
	}

	std::list<Bullet>::iterator it;

	for (it = BulletList.begin(); it != BulletList.end(); it++) {

		it->Update();

		if (it->Position.x < -20
			|| it->Position.x >(float)GetScreenWidth() + 20
			|| it->Position.y < -20
			|| it->Position.y >(float)GetScreenHeight() + 20) {

			it = BulletList.erase(it);
			if (it == BulletList.end()) {
				break;
			}
		}
	}

}

void Player::Draw() {
	DrawTextureEx(PlayerTexture, Position, 0, 4, WHITE);

	// Draw all bullets
	for (auto& bullet : BulletList) {
		bullet.Draw();
	}

#ifdef DEBUG
	DrawText(TextFormat("Debug: bullets %i ", BulletList.size()), 20, GetScreenHeight() - 50, 20, BLACK);
#endif // DEBUG

}
