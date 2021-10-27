#pragma once

#include "Debug.h"

#include <memory>

#include "raylib.h"
#include "raymath.h"

#include "GameObject.h"
#include "Player.h"
#include "Skull.h"


class SkullGame : public GameObject
{
public:
	SkullGame();

	void StartGameLoop();
	void Initialize();
	void Restart();

	void Update() override;
	void Draw() override;

private:
	Color m_BackgroundColor = { 50, 36, 89, 255 };
	Color m_BackgroundColorLost = { 102, 0, 0, 255 };
	Color m_TextColor = { 218, 224, 234, 255 };

	bool m_Lost;
	float m_Score;

	//Textures
	Texture2D m_SkullTexture;
	Texture2D m_PlayerTexture;
	Texture2D m_BulletTexture;

	// Player
	std::unique_ptr<Player> m_Player;

	// Skulls
	std::list<Skull> m_SkullList;
	float m_TimeUntilSkullSpawn;
	float m_SpawnMultiplier;
};
