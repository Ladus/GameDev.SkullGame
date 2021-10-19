#include "raylib.h"
#include "raymath.h"

#include "skull.cpp"
#include <list>

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 960;
	const int screenHeight = 480;

	InitWindow(screenWidth, screenHeight, "RLParticles - Roopis Playground");

	// Game variables
	Color backgroundColor = { 50, 36, 89, 255 };
	Color backgroundColorLost = { 102, 0, 0, 255 };

	Color textColor = { 218, 224, 234, 255 };

	Vector2 targetPosition = { 0,0 };

	bool lost = false;

	float score = 0;

	// Skulls
	std::list<Skull> skullList;
	skullList.emplace_back();
	float timeUntilSkullSpawn = 4;
	float spawnMultiplier = 1.0f;


	SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
	//---------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		//Skull and mouse movement
		targetPosition = Vector2Subtract(GetMousePosition(), { 16, 16 });

		// Skull spawn

		if (GetKeyPressed() == KEY_R) {
			lost = false;
			skullList.clear();
			skullList.emplace_back();
			timeUntilSkullSpawn = 4;
			spawnMultiplier = 1.0f;
			score = 0;
		}

		spawnMultiplier -= 0.02f * GetFrameTime();
		timeUntilSkullSpawn -= 1 * GetFrameTime();
		if (timeUntilSkullSpawn < 0) 
		{
			skullList.emplace_back();
			timeUntilSkullSpawn = (float)GetRandomValue(1, 3) * spawnMultiplier;
		}

		for (auto& skull : skullList)
		{
			skull.Position = Vector2MoveTowards(skull.Position, targetPosition, skull.Speed * GetFrameTime());
			skull.Position = Vector2Add(skull.Position, Vector2Multiply(skull.RandomDeviation, {GetFrameTime(), GetFrameTime()}));

			if (skull.Speed < skull.SpeedLimit) {
				skull.Speed += skull.SpeedIncrement * GetFrameTime();
			}

			// Losing
			if (Vector2Distance(targetPosition, skull.Position) < 16) {
				lost = true;
			}
		}

		if (GetMousePosition().x < 10
			|| (int)GetMousePosition().x > GetScreenWidth() - 10
			|| GetMousePosition().y < 10
			|| (int) GetMousePosition().y > GetScreenHeight() - 10)
		{
			lost = true;
		}

		// Score
		if (!lost) {
			score += 1000 * GetFrameTime();
		}

		// Score

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();


		if (!lost) {
			ClearBackground(backgroundColor);
			DrawText(TextFormat("Run away for the skulls Deepjeee!!!  Score: %i", (int)score), 10, 10, 20, textColor);
		}
		else {
			ClearBackground(backgroundColorLost);
			DrawText(TextFormat("You died.... :(   Final Score: %i", (int)score), 10, 10, 20, textColor);
		}

		for (const auto& skull : skullList)
		{
			DrawTextureEx(skull.Texture, skull.Position, 0, 4, WHITE);
		}

		// Debug
		DrawText(TextFormat("Mouse: %f, %f", GetMousePosition().x, GetMousePosition().y), 10, 400, 20, textColor);
		DrawText(TextFormat("TimeToSpawn: %f", timeUntilSkullSpawn), 10, 420, 20, textColor);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}