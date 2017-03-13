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
public:
	float left;
	float right;
	float bottom;
	float top;
};




//TODO
//object types :
//Rectangle(defined by left, right, bottom, top)
//Ball(rect, by radius), uses drawball from spritecodex
//Brick
//Paddle(halfwith, halfheight dims)
//
//behaviors :
//	Draw,
//	IsOverLappingWith test(use poo logic)
//	bricks need to only render if not destroyed
//	ball needs dowallcollision, then reboundx and reboundy for bounce(bool to play sound)
//	ball and paddle needs function to getRect
//	bricks need doballcollision, then call rebound on ball
//	play sound when bouncing off wall, paddle
//	paddle needs doballcollision, then rebound ball
//	paddle needs dowallcollision(or just include in draw ? )
//
//	rect needs added getexpanded function that returns a rect with padding(used to put padding between bricks)
//
//
//	notes:
//use constructor overloading to make constructors from :
//topleft, bottomright vects
//topleft, width, height,
//center, halfwidth, halfheight(use static member function to call another constructor as workaround)
//
//add a drawrect to graphics.h that uses rectf class to handle draws
//
//wall bouncing can be handled by making a rect of the window size(bounce off the inside of the rect)
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