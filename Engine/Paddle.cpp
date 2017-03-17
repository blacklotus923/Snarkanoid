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
	using std::min;
	const RectF rekt = GetRekt();
	const RectF ballRekt = _ball.GetRekt();
	if (rekt.IsOverlappingWith(ballRekt))
	{
		const float lDelta = abs(rekt.left - ballRekt.right);
		const float rDelta = abs(rekt.right - ballRekt.left);
		const float tDelta = abs(rekt.top - ballRekt.bottom);
		const float bDelta = abs(rekt.bottom - ballRekt.top);
		const float smallest = min(lDelta, min(rDelta, min(tDelta, bDelta)));
		const float c2c = ballRekt.GetCenter().x - rekt.GetCenter().x;

		if (smallest == lDelta)  //leftside
		{
			_ball.ReboundX();
			_ball.ReboundY();
			_ball.Move(Vec2(rekt.left - ballRekt.right, 0.0f));
			_ball.AdjustVel(Vec2(c2c, 0.0f));
		}
		else if (smallest == rDelta)  //rightside
		{
			_ball.ReboundX();
			_ball.ReboundY();
			_ball.Move(Vec2(rekt.right - ballRekt.left, 0.0f));
			_ball.AdjustVel(Vec2(c2c, 0.0f));
		}
		if (smallest == tDelta)  //topside
		{
			_ball.ReboundY();
			_ball.Move(Vec2(0.0f, rekt.top - ballRekt.bottom));
			_ball.AdjustVel(Vec2(c2c, 0.0f));
		}
		else if (smallest == bDelta)  //bottomside
		{
			_ball.ReboundY();
			_ball.Move(Vec2(0.0f, rekt.bottom - ballRekt.top));
		}
		return true;
	}
	return false;
}

RectF Paddle::GetRekt() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
