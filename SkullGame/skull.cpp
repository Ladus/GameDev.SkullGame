#include "raylib.h"
#include "raymath.h"

#include "GameObject.cpp"

class Skull : public GameObject {
public:

	Vector2* TargetPosition;
	Texture2D* SkullTexture;

	Vector2 Position = { (float)GetRandomValue(0, GetScreenWidth()), 0.0f };

	Vector2 RandomDeviation = { (float)GetRandomValue(-3, 3), (float)GetRandomValue(-3, 3) };

	float Speed = (float)GetRandomValue(80, 150);
	float SpeedIncrement = (float)GetRandomValue(15, 30);
	float SpeedLimit = (float)GetRandomValue(500, 800);
	


	explicit Skull(Vector2* targetPosition, Texture2D* skullTexture) 
		: TargetPosition(targetPosition)
		, SkullTexture(skullTexture) { }

	void Update() override {
		Position = Vector2Add(Position, Vector2Multiply(RandomDeviation, { GetFrameTime(), GetFrameTime() }));

		if (Speed < SpeedLimit) {
			Speed += SpeedIncrement * GetFrameTime();
		}

		Position = Vector2MoveTowards(Position, *TargetPosition, Speed * GetFrameTime());
	}

	void Draw() override {
		DrawTextureEx(*SkullTexture, Position, 0, 4, WHITE);
	}
};
