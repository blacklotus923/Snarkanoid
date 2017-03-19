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

//Arkanoid-like paddle bounce variation

//game over when ball hits bottom of screen

//narrower wall layout, adjust size of bricks and paddle

//add pretty border to walls

//add lives

//proper title screen

//proper game over screen

//new paddle sprite, shading on bricks

//more than one brick type

//win when all bricks gone

//multiple levels