#include "Brick.h"
#include <algorithm>
#undef min
#undef max

Brick::Brick(const RectF & _rekt, Color c)
	:
	rekt(_rekt),
	c(c)
{
}

void Brick::Draw(Graphics & _gfx) const
{
	if (!isDestroyed) _gfx.DrawRect(rekt.GetExpanded(-padX,-padY), c);
}

bool Brick::CheckBallCollision(const Ball & _ball) const
{
	return !isDestroyed && rekt.IsOverlappingWith(_ball.GetRekt());
}

void Brick::DoBallCollision(Ball & _ball)
{
	const RectF ballRekt = _ball.GetRekt();
	const float lDelta = abs(rekt.left - ballRekt.right);
	const float rDelta = abs(rekt.right - ballRekt.left);
	const float tDelta = abs(rekt.top - ballRekt.bottom);
	const float bDelta = abs(rekt.bottom - ballRekt.top);
	const float smallest = std::min(lDelta, std::min(rDelta, std::min(tDelta, bDelta)));

	if (smallest == lDelta)  //leftside
	{
		_ball.ReboundX();
		_ball.Move(Vec2(rekt.left - ballRekt.right, 0.0f));
	}
	else if (smallest == rDelta)  //rightside
	{
		_ball.ReboundX();
		_ball.Move(Vec2(rekt.right - ballRekt.left, 0.0f));
	}
	if (smallest == tDelta)  //topside
	{
		_ball.ReboundY();
		_ball.Move(Vec2(0.0f, rekt.top - ballRekt.bottom));
	}
	else if (smallest == bDelta)  //bottomside
	{
		_ball.ReboundY();
		_ball.Move(Vec2(0.0f, rekt.bottom - ballRekt.top));
	}
	isDestroyed = true;
}

RectF Brick::GetRekt() const
{
	return rekt;
}
