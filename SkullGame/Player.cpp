#include "raylib.h"
#include "raymath.h"

#include "GameObject.h"

class Player : public GameObject {
public:

	Texture2D* PlayerTexture;

	Vector2 Position = {
		((float)GetScreenWidth() / 2) - ((float)PlayerTexture->width / 2),
		((float)GetScreenHeight() / 2) - ((float)PlayerTexture->height / 2)
	};
	Vector2 MouseDirection = { 0, 1 };
	Vector2 MovementDirection = { 0, 0 };

	float Speed = 1;

	explicit Player(Texture2D* playerTexture)
		: PlayerTexture(playerTexture) { }

	void Update() override {
		// Keyboard movement
		MovementDirection = { 0, 0 };
		if (IsKeyPressed(KEY_W)) {
			MovementDirection = Vector2Add(MovementDirection, { 0, -1 });
		}
		if (IsKeyPressed(KEY_D)) {
			MovementDirection = Vector2Add(MovementDirection, { 1, 0 });
		}
		if (IsKeyPressed(KEY_S)) {
			MovementDirection = Vector2Add(MovementDirection, { 0, 1 });
		}
		if (IsKeyPressed(KEY_A)) {
			MovementDirection = Vector2Add(MovementDirection, { -1, 0 });
		}

		// Update Position
		Position = Vector2Add(Position, Vector2Multiply(Vector2Multiply(MovementDirection, { Speed, Speed }), { GetFrameTime(), GetFrameTime() }));
	}

	void Draw() override {
		DrawTextureEx(*PlayerTexture, Position, 0, 4, WHITE);

		DrawText(TextFormat("Pos: %f %f", MovementDirection.x, MovementDirection.y), 20, 200, 20, BLACK);
	}
};
