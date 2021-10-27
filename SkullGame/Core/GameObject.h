#pragma once
#include "Debug.h"

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;
};