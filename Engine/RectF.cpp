#include "RectF.h"


RectF::RectF(float _left, float _right, float _bottom, float _top)
	:
	left(_left),
	right(_right),
	bottom(_bottom),
	top(_top)
{
}

RectF::RectF(const Vec2 & _topleft, const Vec2 & _bottomright)
	:
	RectF(_topleft.x,_bottomright.x,_bottomright.y,_topleft.y)
{
}

RectF::RectF(const Vec2 & _topleft, float _width, float _height)
	:
	RectF(_topleft, _topleft+Vec2(_width,_height))
{
}

RectF& RectF::FromCenter(const Vec2 & _center, float _halfWidth, float _halfHeight)
{
	const Vec2 h = {_halfWidth, _halfHeight};
	return RectF(_center-h, _center+h);
}

bool RectF::IsOverlappingWith(const RectF & _rect) const
{
	return left < _rect.right
		&& right > _rect.left
		&& top < _rect.bottom
		&& bottom > _rect.top;
}

RectF RectF::GetExpanded(float _xpad, float _ypad) const
{
	return RectF{ left - _xpad, right + _xpad, bottom + _ypad, top - _ypad };
}
