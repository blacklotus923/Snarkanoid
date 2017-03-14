#include "Brick.h"

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

	if (!isDestroyed && rekt.IsOverlappingWith(_ball.GetRekt()))
	{
		isDestroyed = true;
		_ball.ReboundY();
		return true;
	}
	else return false;

}
