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
	const RectF rekt = GetRekt();
	bool triggered = false;
	if (rekt.left < _walls.left)
	{
		triggered = true;
		ReboundX();
		pos.x += _walls.left - rekt.left;
	}
	else if (rekt.right > _walls.right)
	{
		triggered = true;
		ReboundX();
		pos.x -= rekt.right - _walls.right;
	}
	if (rekt.top < _walls.top)
	{
		triggered = true;
		ReboundY();
		pos.y += _walls.top - rekt.top;
	}
	else if (rekt.bottom > _walls.bottom)
	{
		triggered = true;
		ReboundY();
		pos.y -= rekt.bottom - _walls.bottom;
	}
	return triggered;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

void Ball::AdjustVel(const Vec2 & _delta)
{
	vel += _delta;
}

void Ball::SetVelocity(const Vec2 & _vel)
{
	vel = _vel.GetNormalized()*speed;
}

RectF Ball::GetRekt() const
{
	return RectF::FromCenter(pos, radius, radius);
}

Vec2 Ball::GetVel() const
{
	return vel;
}

void Ball::Move(const Vec2 & _vec)
{
	pos += _vec;
}

void Ball::MoveTo(const Vec2 & _vec)
{
	pos = _vec;
}

bool Ball::IsLaunched() const
{
	return isLaunched;
}

void Ball::Launch(const float _speed)
{
	speed = _speed;
	isLaunched = true;
}

void Ball::Reset()
{
	isLaunched = false;
}
