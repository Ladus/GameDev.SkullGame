#include "Collision.h"

bool BoxCollision(const Rectangle &A, const Rectangle &B)
{
	return A.x < B.x + B.width
		&& A.x + A.width > B.x
		&& A.y < B.y + B.height
		&& A.y + A.height > B.y;
}