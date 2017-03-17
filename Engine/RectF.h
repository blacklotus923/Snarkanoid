#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float _left, float _right, float _bottom, float _top);
	RectF(const Vec2& _topleft, const Vec2& _bottomright);
	RectF(const Vec2& _topleft, float _width, float _height);
	static RectF FromCenter(const Vec2& _center, float _halfWidth, float _halfHeight);
	bool IsOverlappingWith(const RectF& _rect) const;
	RectF GetExpanded(float _xpad, float _ypad) const;
	Vec2 GetCenter() const;
public:
	float left;
	float right;
	float bottom;
	float top;
};




//TODO

//	notes:

//
//Add "Cooldown" to paddle such that ball can only hit paddle once until it's hit a wall or brick again
//Add "closest collision" logic to bricks, such that game.cpp only executes collision on one brick per collision