#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Ball.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Paddle
{
public:
	Paddle(Vec2& _pos, float _halfW, float _halfH);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd, const Mouse& mouse, float dt, const RectF& _walls);
	void DoWallCollision(const RectF& _walls);
	bool DoBallCollision(Ball& _ball);
	void ResetCooldown();
	RectF GetRekt() const;
private:
	void DrawLeftWing(Graphics& gfx) const;
	void DrawMiddle(Graphics& gfx) const;
	void DrawRightWing(Graphics& gfx) const;

private:
	Color c = Colors::White;
	Color wCol = Colors::Red;
	Vec2 pos;
	float wSize = 16.0f;
	float halfWidth;
	float halfHeight;
	float speed = 250.0f;
	bool inCooldown = false;
};

