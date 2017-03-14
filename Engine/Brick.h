#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& _rekt, Color c);
	void Draw(Graphics& _gfx) const;
	bool DoBallCollision(Ball& _ball);

private:
	RectF rekt;
	Color c;
	float padX = 1.0f;
	float padY = 1.0f;
	bool isDestroyed = false;
};

