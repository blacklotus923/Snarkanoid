#include "Paddle.h"
#undef min

Paddle::Paddle(Vec2 & _pos, float _halfW, float _halfH)
	:
	pos(_pos),
	halfWidth(_halfW),
	halfHeight(_halfH)
{
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
		float angle = (ballPos.x - rekt.left) / (halfWidth * 2.0f);
		float theta = -45 * (1 - angle) + 45 * angle;
		if (std::signbit(_ball.GetVel().x) == std::signbit((ballPos - rekt.GetCenter()).x))
		{
			_ball.ReboundY();
			_ball.SetVelocity(_ball.GetVel().GetRotated(theta));
		}
		else if(ballPos.x >= rekt.left && ballPos.x <= rekt.right)
		{
			_ball.ReboundY();
			_ball.SetVelocity(_ball.GetVel().GetRotated(theta));
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

void Paddle::Draw(Graphics & gfx) const
{
	DrawLeftWing(gfx);
	DrawRightWing(gfx);
	DrawMiddle(gfx);
}

void Paddle::DrawLeftWing(Graphics & gfx) const
{
	const int x = (int)(pos.x - halfWidth);
	const int y = (int)(pos.y - halfHeight);
	gfx.PutPixel(6 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(7 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(8 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(9 + x, 0 + y, 181, 24, 0);
	gfx.PutPixel(10 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(11 + x, 0 + y, 181, 24, 0);
	gfx.PutPixel(12 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(13 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(14 + x, 0 + y, 122, 122, 122);
	gfx.PutPixel(5 + x, 1 + y, 180, 23, 0);
	gfx.PutPixel(6 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(7 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(8 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(9 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(10 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(11 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(12 + x, 1 + y, 205, 30, 1);
	gfx.PutPixel(13 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(14 + x, 1 + y, 60, 60, 60);
	gfx.PutPixel(15 + x, 1 + y, 122, 122, 122);
	gfx.PutPixel(4 + x, 2 + y, 180, 23, 0);
	gfx.PutPixel(5 + x, 2 + y, 205, 30, 1);
	gfx.PutPixel(6 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(7 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(8 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(9 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(10 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(11 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(12 + x, 2 + y, 231, 44, 7);
	gfx.PutPixel(13 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(14 + x, 2 + y, 30, 31, 32);
	gfx.PutPixel(15 + x, 2 + y, 60, 60, 60);
	gfx.PutPixel(3 + x, 3 + y, 0, 47, 164);
	gfx.PutPixel(4 + x, 3 + y, 206, 30, 2);
	gfx.PutPixel(5 + x, 3 + y, 232, 45, 7);
	gfx.PutPixel(6 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(7 + x, 3 + y, 241, 122, 66);
	gfx.PutPixel(8 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(9 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(10 + x, 3 + y, 241, 122, 66);
	gfx.PutPixel(11 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(12 + x, 3 + y, 240, 122, 66);
	gfx.PutPixel(13 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(14 + x, 3 + y, 31, 31, 32);
	gfx.PutPixel(15 + x, 3 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 4 + y, 0, 47, 164);
	gfx.PutPixel(3 + x, 4 + y, 0, 108, 231);
	gfx.PutPixel(4 + x, 4 + y, 232, 45, 7);
	gfx.PutPixel(5 + x, 4 + y, 240, 122, 66);
	gfx.PutPixel(6 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(7 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(8 + x, 4 + y, 249, 189, 152);
	gfx.PutPixel(9 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(10 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(11 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(12 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(13 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(14 + x, 4 + y, 31, 31, 32);
	gfx.PutPixel(15 + x, 4 + y, 39, 39, 39);
	gfx.PutPixel(1 + x, 5 + y, 1, 49, 111);
	gfx.PutPixel(2 + x, 5 + y, 0, 92, 212);
	gfx.PutPixel(3 + x, 5 + y, 3, 37, 197);
	gfx.PutPixel(4 + x, 5 + y, 240, 121, 65);
	gfx.PutPixel(5 + x, 5 + y, 249, 190, 152);
	gfx.PutPixel(6 + x, 5 + y, 254, 221, 202);
	gfx.PutPixel(7 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(8 + x, 5 + y, 254, 221, 202);
	gfx.PutPixel(9 + x, 5 + y, 254, 222, 202);
	gfx.PutPixel(10 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(11 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(12 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(13 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(14 + x, 5 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 5 + y, 45, 45, 45);
	gfx.PutPixel(1 + x, 6 + y, 0, 107, 230);
	gfx.PutPixel(2 + x, 6 + y, 3, 37, 197);
	gfx.PutPixel(3 + x, 6 + y, 4, 101, 227);
	gfx.PutPixel(4 + x, 6 + y, 249, 190, 152);
	gfx.PutPixel(5 + x, 6 + y, 253, 221, 201);
	gfx.PutPixel(6 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(7 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(8 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(9 + x, 6 + y, 255, 250, 244);
	gfx.PutPixel(10 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(11 + x, 6 + y, 255, 250, 244);
	gfx.PutPixel(12 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(13 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(14 + x, 6 + y, 31, 31, 32);
	gfx.PutPixel(15 + x, 6 + y, 87, 87, 87);
	gfx.PutPixel(0 + x, 7 + y, 1, 49, 111);
	gfx.PutPixel(1 + x, 7 + y, 40, 170, 246);
	gfx.PutPixel(2 + x, 7 + y, 30, 137, 233);
	gfx.PutPixel(3 + x, 7 + y, 89, 170, 236);
	gfx.PutPixel(4 + x, 7 + y, 254, 221, 202);
	gfx.PutPixel(5 + x, 7 + y, 255, 251, 245);
	gfx.PutPixel(6 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(7 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(8 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(9 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(10 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(11 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(12 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(13 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(14 + x, 7 + y, 30, 31, 32);
	gfx.PutPixel(15 + x, 7 + y, 136, 136, 136);
	gfx.PutPixel(0 + x, 8 + y, 1, 83, 181);
	gfx.PutPixel(1 + x, 8 + y, 40, 169, 246);
	gfx.PutPixel(2 + x, 8 + y, 125, 199, 249);
	gfx.PutPixel(3 + x, 8 + y, 233, 243, 254);
	gfx.PutPixel(4 + x, 8 + y, 255, 251, 245);
	gfx.PutPixel(5 + x, 8 + y, 248, 191, 172);
	gfx.PutPixel(6 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(7 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(8 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(9 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(10 + x, 8 + y, 248, 179, 113);
	gfx.PutPixel(11 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(12 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(13 + x, 8 + y, 248, 179, 113);
	gfx.PutPixel(14 + x, 8 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 8 + y, 85, 85, 85);
	gfx.PutPixel(0 + x, 9 + y, 0, 59, 209);
	gfx.PutPixel(1 + x, 9 + y, 139, 209, 255);
	gfx.PutPixel(2 + x, 9 + y, 139, 209, 255);
	gfx.PutPixel(3 + x, 9 + y, 242, 248, 255);
	gfx.PutPixel(4 + x, 9 + y, 242, 173, 148);
	gfx.PutPixel(5 + x, 9 + y, 241, 96, 45);
	gfx.PutPixel(6 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(7 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(8 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(9 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(10 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(11 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(12 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(13 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(14 + x, 9 + y, 30, 30, 31);
	gfx.PutPixel(15 + x, 9 + y, 41, 41, 41);
	gfx.PutPixel(0 + x, 10 + y, 0, 60, 210);
	gfx.PutPixel(1 + x, 10 + y, 40, 169, 246);
	gfx.PutPixel(2 + x, 10 + y, 40, 170, 246);
	gfx.PutPixel(3 + x, 10 + y, 112, 189, 245);
	gfx.PutPixel(4 + x, 10 + y, 232, 45, 7);
	gfx.PutPixel(5 + x, 10 + y, 236, 69, 26);
	gfx.PutPixel(6 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(7 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(8 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(9 + x, 10 + y, 242, 97, 46);
	gfx.PutPixel(10 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(11 + x, 10 + y, 242, 96, 45);
	gfx.PutPixel(12 + x, 10 + y, 242, 96, 45);
	gfx.PutPixel(13 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(14 + x, 10 + y, 30, 31, 32);
	gfx.PutPixel(15 + x, 10 + y, 39, 39, 39);
	gfx.PutPixel(0 + x, 11 + y, 0, 60, 210);
	gfx.PutPixel(1 + x, 11 + y, 2, 33, 183);
	gfx.PutPixel(2 + x, 11 + y, 0, 107, 230);
	gfx.PutPixel(3 + x, 11 + y, 4, 101, 226);
	gfx.PutPixel(4 + x, 11 + y, 205, 29, 1);
	gfx.PutPixel(5 + x, 11 + y, 232, 45, 7);
	gfx.PutPixel(6 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(7 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(8 + x, 11 + y, 236, 69, 26);
	gfx.PutPixel(9 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(10 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(11 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(12 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(13 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(14 + x, 11 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 11 + y, 38, 38, 38);
	gfx.PutPixel(0 + x, 12 + y, 1, 60, 210);
	gfx.PutPixel(1 + x, 12 + y, 2, 32, 180);
	gfx.PutPixel(2 + x, 12 + y, 0, 66, 212);
	gfx.PutPixel(3 + x, 12 + y, 0, 59, 209);
	gfx.PutPixel(4 + x, 12 + y, 181, 24, 0);
	gfx.PutPixel(5 + x, 12 + y, 206, 30, 2);
	gfx.PutPixel(6 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(7 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(8 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(9 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(10 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(11 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(12 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(13 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(14 + x, 12 + y, 30, 30, 31);
	gfx.PutPixel(15 + x, 12 + y, 35, 35, 35);
	gfx.PutPixel(0 + x, 13 + y, 0, 48, 165);
	gfx.PutPixel(1 + x, 13 + y, 1, 32, 180);
	gfx.PutPixel(2 + x, 13 + y, 3, 37, 197);
	gfx.PutPixel(3 + x, 13 + y, 2, 36, 194);
	gfx.PutPixel(4 + x, 13 + y, 174, 22, 0);
	gfx.PutPixel(5 + x, 13 + y, 180, 23, 0);
	gfx.PutPixel(6 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(7 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(8 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(9 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(10 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(11 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(12 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(13 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(14 + x, 13 + y, 30, 30, 31);
	gfx.PutPixel(15 + x, 13 + y, 34, 34, 34);
	gfx.PutPixel(0 + x, 14 + y, 0, 28, 100);
	gfx.PutPixel(1 + x, 14 + y, 0, 92, 213);
	gfx.PutPixel(2 + x, 14 + y, 2, 33, 183);
	gfx.PutPixel(3 + x, 14 + y, 2, 33, 183);
	gfx.PutPixel(4 + x, 14 + y, 161, 19, 0);
	gfx.PutPixel(5 + x, 14 + y, 174, 22, 0);
	gfx.PutPixel(6 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(7 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(8 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(9 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(10 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(11 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(12 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(13 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(14 + x, 14 + y, 30, 30, 31);
	gfx.PutPixel(15 + x, 14 + y, 32, 32, 32);
	gfx.PutPixel(1 + x, 15 + y, 0, 60, 209);
	gfx.PutPixel(2 + x, 15 + y, 2, 37, 197);
	gfx.PutPixel(3 + x, 15 + y, 2, 33, 183);
	gfx.PutPixel(4 + x, 15 + y, 191, 27, 0);
	gfx.PutPixel(5 + x, 15 + y, 162, 20, 0);
	gfx.PutPixel(6 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(7 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(8 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(9 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(10 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(11 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(12 + x, 15 + y, 173, 22, 0);
	gfx.PutPixel(13 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(14 + x, 15 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 15 + y, 30, 30, 30);
	gfx.PutPixel(1 + x, 16 + y, 0, 28, 100);
	gfx.PutPixel(2 + x, 16 + y, 0, 92, 213);
	gfx.PutPixel(3 + x, 16 + y, 2, 37, 197);
	gfx.PutPixel(4 + x, 16 + y, 221, 32, 0);
	gfx.PutPixel(5 + x, 16 + y, 191, 26, 0);
	gfx.PutPixel(6 + x, 16 + y, 161, 20, 0);
	gfx.PutPixel(7 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(8 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(9 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(10 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(11 + x, 16 + y, 161, 20, 0);
	gfx.PutPixel(12 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(13 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(14 + x, 16 + y, 30, 30, 31);
	gfx.PutPixel(15 + x, 16 + y, 27, 27, 27);
	gfx.PutPixel(2 + x, 17 + y, 0, 47, 164);
	gfx.PutPixel(3 + x, 17 + y, 0, 107, 230);
	gfx.PutPixel(4 + x, 17 + y, 174, 22, 0);
	gfx.PutPixel(5 + x, 17 + y, 221, 32, 0);
	gfx.PutPixel(6 + x, 17 + y, 191, 27, 0);
	gfx.PutPixel(7 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(8 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(9 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(10 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(11 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(12 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(13 + x, 17 + y, 191, 27, 0);
	gfx.PutPixel(14 + x, 17 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 17 + y, 25, 25, 25);
	gfx.PutPixel(3 + x, 18 + y, 0, 47, 164);
	gfx.PutPixel(4 + x, 18 + y, 104, 8, 0);
	gfx.PutPixel(5 + x, 18 + y, 174, 22, 0);
	gfx.PutPixel(6 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(7 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(8 + x, 18 + y, 221, 33, 0);
	gfx.PutPixel(9 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(10 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(11 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(12 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(13 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(14 + x, 18 + y, 30, 30, 32);
	gfx.PutPixel(15 + x, 18 + y, 50, 50, 50);
	gfx.PutPixel(4 + x, 19 + y, 52, 4, 0);
	gfx.PutPixel(5 + x, 19 + y, 104, 9, 0);
	gfx.PutPixel(6 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(7 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(8 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(9 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(10 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(11 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(12 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(13 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(14 + x, 19 + y, 50, 50, 50);
	gfx.PutPixel(15 + x, 19 + y, 78, 78, 78);
	gfx.PutPixel(5 + x, 20 + y, 52, 4, 0);
	gfx.PutPixel(6 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(7 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(8 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(9 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(10 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(11 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(12 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(13 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(14 + x, 20 + y, 77, 77, 77);
	gfx.PutPixel(15 + x, 20 + y, 11, 11, 11);
	gfx.PutPixel(6 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(7 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(8 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(9 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(10 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(11 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(12 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(13 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(14 + x, 21 + y, 11, 11, 11);
}

void Paddle::DrawMiddle(Graphics & gfx) const
{
	const int x1 = (int)((pos.x - halfWidth) + wSize);
	const int x2 = (int)((pos.x + halfWidth) - wSize);
	const int y = (int)(pos.y - halfHeight);
	for (int x = x1; x <= x2; ++x)
	{
		gfx.PutPixel(0 + x, 0 + y, 53, 53, 53);
		gfx.PutPixel(0 + x, 1 + y, 83, 83, 83);
		gfx.PutPixel(0 + x, 2 + y, 113, 113, 113);
		gfx.PutPixel(0 + x, 3 + y, 179, 179, 179);
		gfx.PutPixel(0 + x, 4 + y, 217, 217, 217);
		gfx.PutPixel(0 + x, 5 + y, 234, 234, 234);
		gfx.PutPixel(0 + x, 6 + y, 251, 251, 251);
		gfx.PutPixel(0 + x, 7 + y, 227, 227, 227);
		gfx.PutPixel(0 + x, 8 + y, 205, 205, 205);
		gfx.PutPixel(0 + x, 9 + y, 191, 191, 191);
		gfx.PutPixel(0 + x, 10 + y, 175, 175, 175);
		gfx.PutPixel(0 + x, 11 + y, 148, 148, 148);
		gfx.PutPixel(0 + x, 12 + y, 108, 108, 108);
		gfx.PutPixel(0 + x, 13 + y, 79, 79, 79);
		gfx.PutPixel(0 + x, 14 + y, 53, 53, 53);
		gfx.PutPixel(0 + x, 15 + y, 48, 48, 48);
		gfx.PutPixel(0 + x, 16 + y, 40, 40, 40);
		gfx.PutPixel(0 + x, 17 + y, 83, 83, 83);
		gfx.PutPixel(0 + x, 18 + y, 101, 101, 101);
		gfx.PutPixel(0 + x, 19 + y, 67, 67, 67);
		gfx.PutPixel(0 + x, 20 + y, 33, 33, 33);
		gfx.PutPixel(0 + x, 21 + y, 16, 16, 16);
	}
}

void Paddle::DrawRightWing(Graphics & gfx) const
{
	const int x = (int)((pos.x + halfWidth) - wSize);
	const int y = (int)(pos.y - halfHeight);
	gfx.PutPixel(1 + x, 0 + y, 122, 122, 122);
	gfx.PutPixel(2 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(3 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(4 + x, 0 + y, 181, 24, 0);
	gfx.PutPixel(5 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(6 + x, 0 + y, 181, 24, 0);
	gfx.PutPixel(7 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(8 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(9 + x, 0 + y, 180, 23, 0);
	gfx.PutPixel(0 + x, 1 + y, 122, 122, 122);
	gfx.PutPixel(1 + x, 1 + y, 60, 60, 60);
	gfx.PutPixel(2 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(3 + x, 1 + y, 205, 30, 1);
	gfx.PutPixel(4 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(5 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(6 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(7 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(8 + x, 1 + y, 206, 30, 2);
	gfx.PutPixel(9 + x, 1 + y, 205, 29, 1);
	gfx.PutPixel(10 + x, 1 + y, 180, 23, 0);
	gfx.PutPixel(0 + x, 2 + y, 60, 60, 60);
	gfx.PutPixel(1 + x, 2 + y, 30, 31, 32);
	gfx.PutPixel(2 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(3 + x, 2 + y, 231, 44, 7);
	gfx.PutPixel(4 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(5 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(6 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(7 + x, 2 + y, 231, 44, 6);
	gfx.PutPixel(8 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(9 + x, 2 + y, 232, 45, 7);
	gfx.PutPixel(10 + x, 2 + y, 205, 30, 1);
	gfx.PutPixel(11 + x, 2 + y, 180, 23, 0);
	gfx.PutPixel(0 + x, 3 + y, 30, 30, 32);
	gfx.PutPixel(1 + x, 3 + y, 31, 31, 32);
	gfx.PutPixel(2 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(3 + x, 3 + y, 240, 122, 66);
	gfx.PutPixel(4 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(5 + x, 3 + y, 241, 122, 66);
	gfx.PutPixel(6 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(7 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(8 + x, 3 + y, 241, 122, 66);
	gfx.PutPixel(9 + x, 3 + y, 240, 122, 65);
	gfx.PutPixel(10 + x, 3 + y, 232, 45, 7);
	gfx.PutPixel(11 + x, 3 + y, 206, 30, 2);
	gfx.PutPixel(12 + x, 3 + y, 0, 47, 164);
	gfx.PutPixel(0 + x, 4 + y, 39, 39, 39);
	gfx.PutPixel(1 + x, 4 + y, 31, 31, 32);
	gfx.PutPixel(2 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(3 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(4 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(5 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(6 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(7 + x, 4 + y, 249, 189, 152);
	gfx.PutPixel(8 + x, 4 + y, 249, 190, 153);
	gfx.PutPixel(9 + x, 4 + y, 249, 190, 152);
	gfx.PutPixel(10 + x, 4 + y, 240, 122, 66);
	gfx.PutPixel(11 + x, 4 + y, 232, 45, 7);
	gfx.PutPixel(12 + x, 4 + y, 0, 108, 231);
	gfx.PutPixel(13 + x, 4 + y, 0, 47, 164);
	gfx.PutPixel(0 + x, 5 + y, 45, 45, 45);
	gfx.PutPixel(1 + x, 5 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(3 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(4 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(5 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(6 + x, 5 + y, 254, 222, 202);
	gfx.PutPixel(7 + x, 5 + y, 254, 221, 202);
	gfx.PutPixel(8 + x, 5 + y, 253, 221, 201);
	gfx.PutPixel(9 + x, 5 + y, 254, 221, 202);
	gfx.PutPixel(10 + x, 5 + y, 249, 190, 152);
	gfx.PutPixel(11 + x, 5 + y, 240, 121, 65);
	gfx.PutPixel(12 + x, 5 + y, 3, 37, 197);
	gfx.PutPixel(13 + x, 5 + y, 0, 92, 212);
	gfx.PutPixel(14 + x, 5 + y, 1, 49, 111);
	gfx.PutPixel(0 + x, 6 + y, 87, 87, 87);
	gfx.PutPixel(1 + x, 6 + y, 31, 31, 32);
	gfx.PutPixel(2 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(3 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(4 + x, 6 + y, 255, 250, 244);
	gfx.PutPixel(5 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(6 + x, 6 + y, 255, 250, 244);
	gfx.PutPixel(7 + x, 6 + y, 255, 251, 245);
	gfx.PutPixel(8 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(9 + x, 6 + y, 255, 251, 244);
	gfx.PutPixel(10 + x, 6 + y, 253, 221, 201);
	gfx.PutPixel(11 + x, 6 + y, 249, 190, 152);
	gfx.PutPixel(12 + x, 6 + y, 4, 101, 227);
	gfx.PutPixel(13 + x, 6 + y, 3, 37, 197);
	gfx.PutPixel(14 + x, 6 + y, 0, 107, 230);
	gfx.PutPixel(0 + x, 7 + y, 136, 136, 136);
	gfx.PutPixel(1 + x, 7 + y, 30, 31, 32);
	gfx.PutPixel(2 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(3 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(4 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(5 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(6 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(7 + x, 7 + y, 251, 215, 193);
	gfx.PutPixel(8 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(9 + x, 7 + y, 251, 216, 193);
	gfx.PutPixel(10 + x, 7 + y, 255, 251, 245);
	gfx.PutPixel(11 + x, 7 + y, 254, 221, 202);
	gfx.PutPixel(12 + x, 7 + y, 89, 170, 236);
	gfx.PutPixel(13 + x, 7 + y, 30, 137, 233);
	gfx.PutPixel(14 + x, 7 + y, 40, 170, 246);
	gfx.PutPixel(15 + x, 7 + y, 1, 49, 111);
	gfx.PutPixel(0 + x, 8 + y, 85, 85, 85);
	gfx.PutPixel(1 + x, 8 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 8 + y, 248, 179, 113);
	gfx.PutPixel(3 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(4 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(5 + x, 8 + y, 248, 179, 113);
	gfx.PutPixel(6 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(7 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(8 + x, 8 + y, 247, 178, 112);
	gfx.PutPixel(9 + x, 8 + y, 248, 178, 113);
	gfx.PutPixel(10 + x, 8 + y, 248, 191, 172);
	gfx.PutPixel(11 + x, 8 + y, 255, 251, 245);
	gfx.PutPixel(12 + x, 8 + y, 233, 243, 254);
	gfx.PutPixel(13 + x, 8 + y, 125, 199, 249);
	gfx.PutPixel(14 + x, 8 + y, 40, 169, 246);
	gfx.PutPixel(15 + x, 8 + y, 1, 83, 181);
	gfx.PutPixel(0 + x, 9 + y, 41, 41, 41);
	gfx.PutPixel(1 + x, 9 + y, 30, 30, 31);
	gfx.PutPixel(2 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(3 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(4 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(5 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(6 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(7 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(8 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(9 + x, 9 + y, 244, 144, 77);
	gfx.PutPixel(10 + x, 9 + y, 241, 96, 45);
	gfx.PutPixel(11 + x, 9 + y, 242, 173, 148);
	gfx.PutPixel(12 + x, 9 + y, 242, 248, 255);
	gfx.PutPixel(13 + x, 9 + y, 139, 209, 255);
	gfx.PutPixel(14 + x, 9 + y, 139, 209, 255);
	gfx.PutPixel(15 + x, 9 + y, 0, 59, 209);
	gfx.PutPixel(0 + x, 10 + y, 39, 39, 39);
	gfx.PutPixel(1 + x, 10 + y, 30, 31, 32);
	gfx.PutPixel(2 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(3 + x, 10 + y, 242, 96, 45);
	gfx.PutPixel(4 + x, 10 + y, 242, 96, 45);
	gfx.PutPixel(5 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(6 + x, 10 + y, 242, 97, 46);
	gfx.PutPixel(7 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(8 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(9 + x, 10 + y, 241, 96, 45);
	gfx.PutPixel(10 + x, 10 + y, 236, 69, 26);
	gfx.PutPixel(11 + x, 10 + y, 232, 45, 7);
	gfx.PutPixel(12 + x, 10 + y, 112, 189, 245);
	gfx.PutPixel(13 + x, 10 + y, 40, 170, 246);
	gfx.PutPixel(14 + x, 10 + y, 40, 169, 246);
	gfx.PutPixel(15 + x, 10 + y, 0, 60, 210);
	gfx.PutPixel(0 + x, 11 + y, 38, 38, 38);
	gfx.PutPixel(1 + x, 11 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(3 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(4 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(5 + x, 11 + y, 235, 69, 26);
	gfx.PutPixel(6 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(7 + x, 11 + y, 236, 69, 26);
	gfx.PutPixel(8 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(9 + x, 11 + y, 236, 69, 27);
	gfx.PutPixel(10 + x, 11 + y, 232, 45, 7);
	gfx.PutPixel(11 + x, 11 + y, 205, 29, 1);
	gfx.PutPixel(12 + x, 11 + y, 4, 101, 226);
	gfx.PutPixel(13 + x, 11 + y, 0, 107, 230);
	gfx.PutPixel(14 + x, 11 + y, 2, 33, 183);
	gfx.PutPixel(15 + x, 11 + y, 0, 60, 210);
	gfx.PutPixel(0 + x, 12 + y, 35, 35, 35);
	gfx.PutPixel(1 + x, 12 + y, 30, 30, 31);
	gfx.PutPixel(2 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(3 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(4 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(5 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(6 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(7 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(8 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(9 + x, 12 + y, 232, 45, 7);
	gfx.PutPixel(10 + x, 12 + y, 206, 30, 2);
	gfx.PutPixel(11 + x, 12 + y, 181, 24, 0);
	gfx.PutPixel(12 + x, 12 + y, 0, 59, 209);
	gfx.PutPixel(13 + x, 12 + y, 0, 66, 212);
	gfx.PutPixel(14 + x, 12 + y, 2, 32, 180);
	gfx.PutPixel(15 + x, 12 + y, 1, 60, 210);
	gfx.PutPixel(0 + x, 13 + y, 34, 34, 34);
	gfx.PutPixel(1 + x, 13 + y, 30, 30, 31);
	gfx.PutPixel(2 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(3 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(4 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(5 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(6 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(7 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(8 + x, 13 + y, 205, 29, 1);
	gfx.PutPixel(9 + x, 13 + y, 206, 30, 2);
	gfx.PutPixel(10 + x, 13 + y, 180, 23, 0);
	gfx.PutPixel(11 + x, 13 + y, 174, 22, 0);
	gfx.PutPixel(12 + x, 13 + y, 2, 36, 194);
	gfx.PutPixel(13 + x, 13 + y, 3, 37, 197);
	gfx.PutPixel(14 + x, 13 + y, 1, 32, 180);
	gfx.PutPixel(15 + x, 13 + y, 0, 48, 165);
	gfx.PutPixel(0 + x, 14 + y, 32, 32, 32);
	gfx.PutPixel(1 + x, 14 + y, 30, 30, 31);
	gfx.PutPixel(2 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(3 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(4 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(5 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(6 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(7 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(8 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(9 + x, 14 + y, 180, 23, 0);
	gfx.PutPixel(10 + x, 14 + y, 174, 22, 0);
	gfx.PutPixel(11 + x, 14 + y, 161, 19, 0);
	gfx.PutPixel(12 + x, 14 + y, 2, 33, 183);
	gfx.PutPixel(13 + x, 14 + y, 2, 33, 183);
	gfx.PutPixel(14 + x, 14 + y, 0, 92, 213);
	gfx.PutPixel(15 + x, 14 + y, 0, 28, 100);
	gfx.PutPixel(0 + x, 15 + y, 30, 30, 30);
	gfx.PutPixel(1 + x, 15 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(3 + x, 15 + y, 173, 22, 0);
	gfx.PutPixel(4 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(5 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(6 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(7 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(8 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(9 + x, 15 + y, 174, 22, 0);
	gfx.PutPixel(10 + x, 15 + y, 162, 20, 0);
	gfx.PutPixel(11 + x, 15 + y, 191, 27, 0);
	gfx.PutPixel(12 + x, 15 + y, 2, 33, 183);
	gfx.PutPixel(13 + x, 15 + y, 2, 37, 197);
	gfx.PutPixel(14 + x, 15 + y, 0, 60, 209);
	gfx.PutPixel(0 + x, 16 + y, 27, 27, 27);
	gfx.PutPixel(1 + x, 16 + y, 30, 30, 31);
	gfx.PutPixel(2 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(3 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(4 + x, 16 + y, 161, 20, 0);
	gfx.PutPixel(5 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(6 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(7 + x, 16 + y, 161, 19, 0);
	gfx.PutPixel(8 + x, 16 + y, 162, 20, 0);
	gfx.PutPixel(9 + x, 16 + y, 161, 20, 0);
	gfx.PutPixel(10 + x, 16 + y, 191, 26, 0);
	gfx.PutPixel(11 + x, 16 + y, 221, 32, 0);
	gfx.PutPixel(12 + x, 16 + y, 2, 37, 197);
	gfx.PutPixel(13 + x, 16 + y, 0, 92, 213);
	gfx.PutPixel(14 + x, 16 + y, 0, 28, 100);
	gfx.PutPixel(0 + x, 17 + y, 25, 25, 25);
	gfx.PutPixel(1 + x, 17 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 17 + y, 191, 27, 0);
	gfx.PutPixel(3 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(4 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(5 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(6 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(7 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(8 + x, 17 + y, 191, 26, 0);
	gfx.PutPixel(9 + x, 17 + y, 191, 27, 0);
	gfx.PutPixel(10 + x, 17 + y, 221, 32, 0);
	gfx.PutPixel(11 + x, 17 + y, 174, 22, 0);
	gfx.PutPixel(12 + x, 17 + y, 0, 107, 230);
	gfx.PutPixel(13 + x, 17 + y, 0, 47, 164);
	gfx.PutPixel(0 + x, 18 + y, 50, 50, 50);
	gfx.PutPixel(1 + x, 18 + y, 30, 30, 32);
	gfx.PutPixel(2 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(3 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(4 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(5 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(6 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(7 + x, 18 + y, 221, 33, 0);
	gfx.PutPixel(8 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(9 + x, 18 + y, 221, 32, 0);
	gfx.PutPixel(10 + x, 18 + y, 174, 22, 0);
	gfx.PutPixel(11 + x, 18 + y, 104, 8, 0);
	gfx.PutPixel(12 + x, 18 + y, 0, 47, 164);
	gfx.PutPixel(0 + x, 19 + y, 78, 78, 78);
	gfx.PutPixel(1 + x, 19 + y, 50, 50, 50);
	gfx.PutPixel(2 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(3 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(4 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(5 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(6 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(7 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(8 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(9 + x, 19 + y, 174, 22, 0);
	gfx.PutPixel(10 + x, 19 + y, 104, 9, 0);
	gfx.PutPixel(11 + x, 19 + y, 52, 4, 0);
	gfx.PutPixel(0 + x, 20 + y, 11, 11, 11);
	gfx.PutPixel(1 + x, 20 + y, 77, 77, 77);
	gfx.PutPixel(2 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(3 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(4 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(5 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(6 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(7 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(8 + x, 20 + y, 104, 8, 0);
	gfx.PutPixel(9 + x, 20 + y, 104, 9, 0);
	gfx.PutPixel(10 + x, 20 + y, 52, 4, 0);
	gfx.PutPixel(1 + x, 21 + y, 11, 11, 11);
	gfx.PutPixel(2 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(3 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(4 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(5 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(6 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(7 + x, 21 + y, 53, 5, 0);
	gfx.PutPixel(8 + x, 21 + y, 52, 5, 0);
	gfx.PutPixel(9 + x, 21 + y, 52, 5, 0);
}
