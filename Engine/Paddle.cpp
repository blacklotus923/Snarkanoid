#include "Paddle.h"

Paddle::Paddle(Vec2 & _pos, float _halfW, float _halfH)
	:
	pos(_pos),
	halfWidth(_halfW),
	halfHeight(_halfH)
{
}

void Paddle::Draw(Graphics & gfx) const
{
	const RectF rekt = GetRekt();
	gfx.DrawRect(rekt, wCol);
	gfx.DrawRect(rekt.GetExpanded(-wSize, 0.0f),c);
}

void Paddle::Update(const Keyboard& kbd, float dt, const RectF& _walls)
{
	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed('A')) pos.x -= speed * dt;
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed('D')) pos.x += speed * dt;
	DoWallCollision(_walls);
}

void Paddle::DoWallCollision(const RectF& _walls)
{
	const RectF rekt = GetRekt();
	if (rekt.left < _walls.left) pos.x += _walls.left - rekt.left;
	else if (rekt.right > _walls.right) pos.x -= rekt.right - _walls.right;
}

bool Paddle::DoBallCollision(Ball & _ball) const
{
	if (_ball.GetVel().y > 0 && GetRekt().IsOverlappingWith(_ball.GetRekt()))
	{
		_ball.ReboundY();
		return true;
	}
	return false;
}

RectF Paddle::GetRekt() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
