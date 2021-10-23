#include "raylib.h"
#include "raymath.h"

#include "GameObject.cpp"

class Skull : public GameObject {
public:

	Vector2* TargetPosition;
	Texture2D* SkullTexture;

	Vector2 Position = { (float)GetRandomValue(0, GetScreenWidth()), 0.0f };

	float Speed = (float)GetRandomValue(80, 150);
	float SpeedIncrement = (float)GetRandomValue(15, 30);
	float SpeedLimit = (float)GetRandomValue(500, 800);
	
	float RotationSpeed;
	float RotationSpeedMax = (float)GetRandomValue(5, 10);
	float RotationOscillation = (float)GetRandomValue(1, 4);

	float LocalTime = 0;
	float LocalTimeMax = 1;
	
	Vector2 Direction = { 0, 1 };

	explicit Skull(Vector2* targetPosition, Texture2D* skullTexture) 
		: TargetPosition(targetPosition)
		, SkullTexture(skullTexture) { }

	void Update() override {
		// Local time
		if (LocalTime < LocalTimeMax) {
			LocalTime += GetFrameTime();
		}
		else {
			LocalTime = 0;
		}

		// Slowly increase speed
		if (Speed < SpeedLimit) {
			Speed += SpeedIncrement * GetFrameTime();
		}

		// Oscilate the rotationSpeed
		RotationSpeed = RotationSpeedMax - (RotationOscillation * (LocalTime / LocalTimeMax));


		Position = Vector2Add(Position, Direction);

		Direction = Vector2Rotate(Direction, RotationSpeed * GetFrameTime());
		
		// Old way of moving directly
		// Position = Vector2MoveTowards(Position, *TargetPosition, Speed * GetFrameTime());
	}

	void Draw() override {
		DrawTextureEx(*SkullTexture, Position, 0, 4, WHITE);

		DrawRectangle(20, 420, 1000, 20, BLACK);
		DrawText(TextFormat("doei %f", LocalTime / LocalTimeMax), 20, 420, 20, WHITE);
	}
};
