#include "Brick.h"

Brick::Brick(RectF & _rekt, Color c)
	:
	rekt(_rekt),
	c(c)
{
}

void Brick::Draw(Graphics & _gfx) const
{
	if (!isDestroyed) _gfx.DrawRect(rekt, c);
}

bool Brick::DoBallCollision(Ball & _ball)
{
	return false;
}