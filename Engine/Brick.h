#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"

class Brick
{
public:
	enum class Type
	{
		Empty,
		Normal,
		Strong,
		Nobreak,
		Explode,
		Exploded
	};
public:
	Brick() = default;
	Brick(const RectF& _rekt, Color c = Colors::Gray, Type _type = Type::Normal);
	void Draw(Graphics& _gfx) const;
	bool CheckBallCollision(const Ball& _ball) const;
	Type DoBallCollision(Ball& _ball);
	void DoDamage();
	RectF GetRekt() const;
	void Reset();

private:
	Type bType= Type::Empty;
	RectF rekt;
	Color c;
	Color highlight;
	Color lowlight;
	float padX = 1.0f;
	float padY = 1.0f;
	float depth = 3.0f;
	float colorDamageFactor = 0.75f;
	int hitsToDestroy=1;
	bool isDestroyed = false;
};

