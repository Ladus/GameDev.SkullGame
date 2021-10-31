#pragma once

#include <list>
#include "../GameObjects/Skull.h"
#include "../GameObjects/Bullet.h"

void HandleSkullBulletCollision(std::list<Skull> &skullList, std::list<Bullet> &m_BulletList);
void UpdateBullets(std::list<Bullet>& bulletList);