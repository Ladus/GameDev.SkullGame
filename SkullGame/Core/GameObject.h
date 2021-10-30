#pragma once
#include "Debug.h"

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// TODO: Add Position(translation?) and Size (And scale?) as GameObject variables;
};