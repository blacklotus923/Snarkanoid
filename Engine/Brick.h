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
	bool CheckBallCollision(const Ball& _ball) const;
	void DoBallCollision(Ball& _ball);
	RectF GetRekt() const;

private:
	RectF rekt;
	Color c;
	Color highlight;
	Color lowlight;
	float padX = 1.0f;
	float padY = 1.0f;
	float depth = 3.0f;
	bool isDestroyed = false;
};

