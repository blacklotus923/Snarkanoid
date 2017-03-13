#pragma once

#include "Vec2.h"
#include "RectF.h"
#include "SpriteCodex.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(Vec2& _pos, Vec2& _vel);
	void Draw(Graphics& _gfx) const;
	void Update(float dt);
	bool DoWallCollision(const RectF& _walls);
	void ReboundX();
	void ReboundY();
	RectF& GetRekt() const;
	Vec2 GetVel() const;

private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};

