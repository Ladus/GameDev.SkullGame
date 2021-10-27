#include "Debug.h"
#include "raylib.h"
#include "SkullGame.h"

int main(void)
{
	const int screenWidth = 960;
	const int screenHeight = 480;

	InitWindow(screenWidth, screenHeight, "Skull Game");
	SetTargetFPS(60);

	// Main game loop
	SkullGame skullGame;

	skullGame.StartGameLoop();

	// Exit program
	CloseWindow();
	return 0;
}