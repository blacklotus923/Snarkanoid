#include "Ball.h"


Ball::Ball(Vec2 & _pos, Vec2 & _vel)
	:
	pos(_pos),
	vel(_vel)
{
}

void Ball::Draw(Graphics& _gfx) const
{
	SpriteCodex::DrawBall(pos, _gfx);
}

void Ball::Update(float dt)
{
	pos += vel *dt;
}

bool Ball::DoWallCollision(const RectF & _walls)
{
	bool triggered = false;

	return GetRekt().IsOverlappingWith(_walls);
}

RectF & Ball::GetRekt() const
{
	return RectF::FromCenter(pos, radius, radius);
}
