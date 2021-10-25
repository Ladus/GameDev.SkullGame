#include "Debug.h"

#include "raylib.h"
#include "raymath.h"

#include "Skull.h"
#include "Player.h"
#include <list>

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 960;
	const int screenHeight = 480;

	InitWindow(screenWidth, screenHeight, "Skull Game");
	SetTargetFPS(60);

	// Game variables
	Color backgroundColor = { 50, 36, 89, 255 };
	Color backgroundColorLost = { 102, 0, 0, 255 };

	Color textColor = { 218, 224, 234, 255 };

	bool lost = false;

	float score = 0;

	Texture2D SkullTexture = LoadTexture("Assets/skull_stage.png");
	Texture2D PlayerTexture = LoadTexture("Assets/candy_corn_stage.png");
	Texture2D BulletTexture = LoadTexture("Assets/candy_stage.png");

	// Player
	Player Player(&PlayerTexture, &BulletTexture);

	// Skulls
	std::list<Skull> skullList;
	skullList.emplace_back(&Player.Position, &SkullTexture);
	float timeUntilSkullSpawn = 4;
	float spawnMultiplier = 1.0f;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		// Mouse movement
		//targetPosition = Vector2Subtract(GetMousePosition(), { 16, 16 });

		// Skull spawn

		if (GetKeyPressed() == KEY_R) {
			lost = false;
			skullList.clear();
			skullList.emplace_back(&Player.Position, &SkullTexture);
			timeUntilSkullSpawn = 4;
			spawnMultiplier = 1.0f;
			score = 0;
		}

		if (spawnMultiplier > 0.1) {
			spawnMultiplier -= 0.015f * GetFrameTime();
		}
		timeUntilSkullSpawn -= 1 * GetFrameTime();
		if (timeUntilSkullSpawn < 0 && !lost)
		{
			skullList.emplace_back(&Player.Position, &SkullTexture);
			timeUntilSkullSpawn = ((float)GetRandomValue(1, 30) / 10) * spawnMultiplier;
		}

		// Player update
		Player.Update();

		// Skulls update
		for (auto& skull : skullList)
		{
			//Update skull movement
			skull.Update();

			// Lose if skull is too code
			if (Vector2Distance(Player.Position, skull.Position) < 16) {
				lost = true;
			}
		}

		// Lose if the player goes too close to the border
		if (Player.Position.x < 10
			|| (int)Player.Position.x > GetScreenWidth() - 10
			|| Player.Position.y < 10
			|| (int)Player.Position.y > GetScreenHeight() - 10)
		{
			lost = true;
		}

		// Score
		if (!lost) {
			score += 1000 * GetFrameTime();
		}

		// -------------------------------------------
		// Draw
		BeginDrawing();

		// Draw playing of lost screen
		if (!lost) {
			ClearBackground(backgroundColor);
			DrawText(TextFormat("Run away for the skulls!!!  Score: %i", (int)score), 20, 20, 20, textColor);
		}
		else {
			ClearBackground(backgroundColorLost);
			DrawText(TextFormat("You died.... :(  Press 'R' to restart.  Final Score: %i", (int)score), 20, 20, 20, textColor);
		}

		// Draw losing borders
		DrawRectangle(0, 0, GetScreenWidth(), 10, BLACK);
		DrawRectangle(GetScreenWidth() - 10, 0, 10, GetScreenHeight(), BLACK);
		DrawRectangle(0, GetScreenHeight() - 10, GetScreenWidth(), 10, BLACK);
		DrawRectangle(0, 0, 10, GetScreenHeight(), BLACK);

		// Draw player
		Player.Draw();

		//Draw skulls
		for (auto& skull : skullList)
		{
			skull.Draw();
		}

		// Debug
#ifdef DEBUG
		DrawText(TextFormat("Mouse: %f, %f", GetMousePosition().x, GetMousePosition().y), 20, 400, 20, textColor);
		DrawText(TextFormat("TimeToSpawn: %f", timeUntilSkullSpawn), 20, 420, 20, textColor);
#endif // DEBUG

		EndDrawing();
	}

	// Close window and OpenGL context
	CloseWindow();
	return 0;
}