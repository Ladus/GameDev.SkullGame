#include "ObjectManager.h"
#include "../Core/Collision.h"

void HandleSkullBulletCollision(std::list<Skull>& skullList, std::list<Bullet>& bulletList)
{
	for (Skull& skull : skullList)
	{
		//for each bullet
		std::list<Bullet>::iterator it;

		for (it = bulletList.begin(); it != bulletList.end(); it++)
		{
			// Remove bullet from the list upon collision
			if (BoxCollision(it->Rect, skull.Rect))
			{
				// Clamp slowdown
				skull.Slowdown = Clamp(skull.Slowdown - (0.3f * GetFrameTime()), 0, 1);

				it = bulletList.erase(it);
				if (it == bulletList.end()) // Break the loop if there are no bullets left
					break;
			}
		}
	}
}

void UpdateBullets(std::list<Bullet>& bulletList)
{
	std::list<Bullet>::iterator it;

	for (it = bulletList.begin(); it != bulletList.end(); it++)
	{
		it->Update();

		// Remove bullet from the list once it goes outside of the screen
		if (!BoxCollision(
			it->Rect,
			{
				it->Rect.width,
				-it->Rect.height,
				(float)GetScreenWidth() + it->Rect.width,
				(float)GetScreenHeight() + it->Rect.height
			}))
		{
			it = bulletList.erase(it);
			if (it == bulletList.end())
			{
				// Stop loop if there are no bullets left
				break;
			}
		}
	}
}