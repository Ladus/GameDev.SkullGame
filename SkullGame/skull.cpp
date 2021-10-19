#include "raylib.h"
#include "raymath.h"

class Skull {
	public:
		Vector2 Position = { (float)GetRandomValue(0, GetScreenWidth()), 0.0f };
		float Speed = (float) GetRandomValue(80,150);
		float SpeedIncrement = (float)GetRandomValue(15,30);
		float SpeedLimit = (float)GetRandomValue(500,800);
		Texture2D Texture = LoadTexture("Assets/skull_stage.png");
		Vector2 RandomDeviation = { (float) GetRandomValue(-3, 3), (float)GetRandomValue(-3, 3) };
};
