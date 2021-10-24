#include "raylib.h"
#include "raymath.h"

#include "GameObject.h"

class Skull : public GameObject {
public:

	Vector2* TargetPosition;
	Texture2D* SkullTexture;

	Vector2 Position;

	float Speed = (float)GetRandomValue(2, 6) / 10;
	float SpeedIncrement = (float)GetRandomValue(1, 10) / 10;
	float SpeedLimit = (float)GetRandomValue(10, 40) / 10;

	float RotationSpeed = 0;
	float RotationSpeedMax = (float)GetRandomValue(5, 10);

	float LocalTime = (float)GetRandomValue(10, 100) / 10;
	float LocalTimeMax = (float)GetRandomValue(5, 50) / 10;
	bool LocalTimeUp = true;

	Vector2 Direction = { 0, 1 };

	explicit Skull(Vector2* targetPosition, Texture2D* skullTexture)
		: TargetPosition(targetPosition)
		, SkullTexture(skullTexture) {

		int spawnDirection = GetRandomValue(1, 4);
		switch (spawnDirection) {
		case 1:
			Position = { (float)GetRandomValue(0, GetScreenWidth()), -8.0f };
			break;
		case 2:
			Position = { (float)GetScreenWidth(), (float)GetRandomValue(0, GetScreenHeight()) };
			break;
		case 3:
			Position = { (float)GetRandomValue(0, GetScreenWidth()), (float)GetScreenHeight() + 8.0f };
			break;
		case 4:
			Position = { -8.0f, (float)GetRandomValue(0, GetScreenHeight()) };
			break;
		default:
			Position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
		}
	}

	void Update() override {
		// Local time
		if (LocalTimeUp && LocalTime < LocalTimeMax) {
			LocalTime += GetFrameTime();
		}
		else if (!LocalTimeUp && LocalTime > 0) {
			LocalTime -= GetFrameTime();
		}
		else {
			LocalTimeUp = !LocalTimeUp;
		}

		// Slowly increase speed
		if (Speed < SpeedLimit) {
			Speed += SpeedIncrement * GetFrameTime();
		}

		// Oscilate the rotationSpeed
		RotationSpeed = RotationSpeedMax * (LocalTime / LocalTimeMax);

		Vector2 directionLeft = Vector2Rotate(Direction, -RotationSpeed * GetFrameTime());
		Vector2 directionRight = Vector2Rotate(Direction, RotationSpeed * GetFrameTime());

		Vector2 positionRight = Vector2Add(Position, Vector2Scale(directionRight, Speed));
		Vector2 positionLeft = Vector2Add(Position, Vector2Scale(directionLeft, Speed));

		if (Vector2Distance(positionRight, *TargetPosition) < Vector2Distance(positionLeft, *TargetPosition)) {
			Direction = directionRight;
			Position = positionRight;
		}
		else {
			Direction = directionLeft;
			Position = positionLeft;
		}
	}

	void Draw() override {
		DrawTextureEx(*SkullTexture, Position, 0, 4, WHITE);
	}
};
