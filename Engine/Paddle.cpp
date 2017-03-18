#include "Paddle.h"
#undef min

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

void Paddle::Update(const Keyboard& kbd, const Mouse& mouse, float dt, const RectF& _walls)
{
	Vec2 mspos = Vec2((float)mouse.GetPosX(), (float)mouse.GetPosY());
	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed('A')) pos.x -= speed * dt;
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed('D')) pos.x += speed * dt;
	if (mspos.x > 0.0f && mspos.x < Graphics::ScreenWidth) pos.x = mspos.x;
	DoWallCollision(_walls);
}

void Paddle::DoWallCollision(const RectF& _walls)
{
	const RectF rekt = GetRekt();
	if (rekt.left < _walls.left) pos.x += _walls.left - rekt.left;
	else if (rekt.right > _walls.right) pos.x -= rekt.right - _walls.right;
}

bool Paddle::DoBallCollision(Ball & _ball)
{
	const RectF rekt = GetRekt();
	const RectF ballRekt = _ball.GetRekt();
	Vec2 ballSpeed = _ball.GetVel();
	if (!inCooldown && rekt.IsOverlappingWith(ballRekt) && ballSpeed.y > 0.0f)
	{
		Vec2 ballPos = ballRekt.GetCenter();
		Vec2 c2c = ballPos - rekt.GetCenter();
		Vec2 ballVelNorm = ballSpeed.GetNormalized();
		ballVelNorm.y = -ballVelNorm.y;
		Vec2 newDirNormal = (ballVelNorm + (c2c).GetNormalized()).GetNormalized();
		if (std::signbit(_ball.GetVel().x) == std::signbit((ballPos - rekt.GetCenter()).x))
		{
			_ball.Move(Vec2(0.0f, rekt.top - ballRekt.bottom));
			_ball.SetVelocity(newDirNormal);
		}
		else if(ballPos.x >= rekt.left && ballPos.x <= rekt.right)
		{
			_ball.Move(Vec2(0.0f, rekt.top - ballRekt.bottom));
			_ball.SetVelocity(newDirNormal);
		}
		else _ball.ReboundX();		
		inCooldown = true;
		return true;
	}
	return false;
}

void Paddle::ResetCooldown()
{
	inCooldown = false;
}

RectF Paddle::GetRekt() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
