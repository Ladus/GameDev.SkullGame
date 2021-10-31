#include "SkullGame.h"

SkullGame::SkullGame() = default;

void SkullGame::StartGameLoop()
{
	Initialize();
	Restart();

	while (!WindowShouldClose())
	{
		Update();
		Draw();
	}
}

void SkullGame::Initialize()
{
	m_SkullTexture = LoadTexture("Assets/skull_stage.png");
	m_PlayerTexture = LoadTexture("Assets/candy_corn_stage.png");
	m_BulletTexture = LoadTexture("Assets/candy_stage.png");

	m_Player = std::make_unique<Player>(m_PlayerTexture, m_BulletTexture, m_BulletList);

	Restart();
}

void SkullGame::Restart()
{
	m_Lost = false;
	m_Score = 0;

	m_SkullList.emplace_back(&m_Player->Rect, &m_SkullTexture);
	m_TimeUntilSkullSpawn = 4;
	m_SpawnMultiplier = 1.0f;

	m_SkullList.clear();
	m_SkullList.emplace_back(&m_Player->Rect, &m_SkullTexture);
}

void SkullGame::Update()
{
	// Restart if R is pressed
	if (GetKeyPressed() == KEY_R)
	{
		Restart();
	}

	// Slowly increase spawn rate of skulls
	if (m_SpawnMultiplier > 0.1)
	{
		m_SpawnMultiplier -= 0.015f * GetFrameTime();
	}

	m_TimeUntilSkullSpawn -= 1 * GetFrameTime();
	
	if (m_TimeUntilSkullSpawn < 0 && !m_Lost)
	{
		m_SkullList.emplace_back(&m_Player->Rect, &m_SkullTexture);
		m_TimeUntilSkullSpawn = ((float)GetRandomValue(1, 30) / 10) * m_SpawnMultiplier;
	}

	// Add to score while game is going on
	if (!m_Lost)
	{
		m_Score += 1000 * GetFrameTime();
	}

	// Player update
	m_Player->Update();

	// Update bullets
	UpdateBullets(m_BulletList);

	// Update skulls
	for (auto& skull : m_SkullList)
	{
		//Update skull movement
		skull.Update();

		// Lose if skull is too close
		if(BoxCollision(m_Player->Rect, skull.Rect))
		{
			m_Lost = true;
		}
	}

	// Calculate Bullet and skull collisions. On collision erase bullet, and slow skull down
	HandleSkullBulletCollision(m_SkullList, m_BulletList);
}

void SkullGame::Draw()
{
	// Draw
	BeginDrawing();

	// Draw playing of lost screen
	if (!m_Lost)
	{
		ClearBackground(m_BackgroundColor);
		DrawText(TextFormat("Run away for the skulls!!!  Score: %i", (int)m_Score), 20, 20, 20, m_TextColor);
	}
	else
	{
		ClearBackground(m_BackgroundColorLost);
		DrawText(TextFormat("You died.... :(  Press 'R' to restart.  Final Score: %i", (int)m_Score), 20, 20, 20, m_TextColor);
	}

	// Draw losing borders
	DrawRectangle(0, 0, GetScreenWidth(), 10, BLACK);
	DrawRectangle(GetScreenWidth() - 10, 0, 10, GetScreenHeight(), BLACK);
	DrawRectangle(0, GetScreenHeight() - 10, GetScreenWidth(), 10, BLACK);
	DrawRectangle(0, 0, 10, GetScreenHeight(), BLACK);

	// Draw player
	m_Player->Draw();

	// Draw all bullets
	for (auto& bullet : m_BulletList)
	{
		bullet.Draw();
	}

	//Draw skulls
	for (auto& skull : m_SkullList)
	{
		skull.Draw();
	}

	// Debug
//#ifdef DEBUG
//	DrawText(TextFormat("TimeToSpawn: %f", m_TimeUntilSkullSpawn), 20, 420, 20, m_TextColor);
//#endif

	EndDrawing();
}