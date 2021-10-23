#include "raylib.h"
#include "raymath.h"

#include "GameObject.cpp"

class Skull : public GameObject {
public:

	Vector2* TargetPosition;

	Vector2 Position = { (float)GetRandomValue(0, GetScreenWidth()), 0.0f };
	float Speed = (float)GetRandomValue(80, 150);
	float SpeedIncrement = (float)GetRandomValue(15, 30);
	float SpeedLimit = (float)GetRandomValue(500, 800);
	Texture2D Texture = LoadTexture("Assets/skull_stage.png");
	Vector2 RandomDeviation = { (float)GetRandomValue(-3, 3), (float)GetRandomValue(-3, 3) };


	explicit Skull(Vector2* targetPosition) : TargetPosition(targetPosition) { }

	void Update() override {
		Position = Vector2Add(Position, Vector2Multiply(RandomDeviation, { GetFrameTime(), GetFrameTime() }));

		if (Speed < SpeedLimit) {
			Speed += SpeedIncrement * GetFrameTime();
		}

		Position = Vector2MoveTowards(Position, *TargetPosition, Speed * GetFrameTime());
	}

	void Draw() override {
		DrawTextureEx(Texture, Position, 0, 4, WHITE);
	}
};
