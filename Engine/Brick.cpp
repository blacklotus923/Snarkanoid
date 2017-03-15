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

bool Brick::DoBallCollision(Ball & _ball)
{
	using std::min;
	const RectF ballRekt = _ball.GetRekt();
	if (!isDestroyed && rekt.IsOverlappingWith(ballRekt))
	{
		const float lDelta = abs(rekt.left - ballRekt.right);
		const float rDelta = abs(rekt.right - ballRekt.left);
		const float tDelta = abs(rekt.top - ballRekt.bottom);
		const float bDelta = abs(rekt.bottom - ballRekt.top);
		const float smallest = min(lDelta, min(rDelta, min(tDelta, bDelta)));

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
		return true;
	}
	return false;
}
