#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float _left, float _right, float _bottom, float _top);
	RectF(const Vec2& _topleft, const Vec2& _bottomright);
	RectF(const Vec2& _topleft, float _width, float _height);
	static RectF& FromCenter(const Vec2& _center, float _halfWidth, float _halfHeight);
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
//use "board" grid logic for generating bricks in array.use topleft for offset of initial location of grid.
//cooltip :
//	for (brick& b : bricks)
//	{
//		do stuff for each brick in bricks;
//		<break for collision to avoid further checks>
//	}
//
//all the things include ball, but ball includes NO things.no circular dependencies, yo.
//
//add wings of different color to paddle by drawing smaller rect by width - wingwidth