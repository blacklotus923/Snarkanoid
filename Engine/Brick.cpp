#include "Brick.h"
#include <algorithm>
#undef min
#undef max

Brick::Brick(const RectF & _rekt, Color c, Type _type)
	:
	rekt(_rekt),
	c(c),
	bType(_type)
{
	switch (_type)
	{
	case Type::Empty:
		break;
	case Type::Normal:
		break;
	case Type::Strong:
		c = Colors::Gray;
		break;
	case Type::Nobreak:
		c = Colors::Yellow;
		break;
	case Type::Explode:
		c = Colors::Red;
		break;
	default:
		break;
	}
	const float r = (float)c.GetR();
	const float g = (float)c.GetG();
	const float b = (float)c.GetB();
	highlight = Color((int)std::min(r*1.25f, 255.0f), (int)std::min(g*1.25f, 255.0f), (int)std::min(b*1.25f, 255.0f));
	lowlight = Color((int)(r*0.75f), (int)(g*0.75f), (int)(b*0.75f));
}

void Brick::Draw(Graphics & _gfx) const
{
	const RectF brick = rekt.GetExpanded(-padX, -padY);
	const float width = brick.right - brick.left;
	const float height = (brick.bottom - brick.top)-1.5f;
	if (!isDestroyed)
	{
		_gfx.DrawRect(brick.GetExpanded(-depth, -depth), c);
		for (int y = (int)brick.top; y < (int)brick.bottom; y++)
		{
			for (int x = (int)brick.left; x <= (int)brick.right-1.0f; x++)
			{
				if (x < brick.left + depth || y < brick.top + depth || x >= brick.right - depth || y >= brick.bottom - depth)
				{
					if ((x - brick.left) / (width / height) + (y - brick.top) < height)
					{
						_gfx.PutPixel(x, y, highlight);
					}
					else _gfx.PutPixel(x, y, lowlight);
				}
			}
		}
	}
}

bool Brick::CheckBallCollision(const Ball & _ball) const
{
	return !isDestroyed && rekt.IsOverlappingWith(_ball.GetRekt());
}

void Brick::DoBallCollision(Ball & _ball)
{
	const RectF ballRekt = _ball.GetRekt();
	const float lDelta = abs(rekt.left - ballRekt.right);
	const float rDelta = abs(rekt.right - ballRekt.left);
	const float tDelta = abs(rekt.top - ballRekt.bottom);
	const float bDelta = abs(rekt.bottom - ballRekt.top);
	const float smallest = std::min(lDelta, std::min(rDelta, std::min(tDelta, bDelta)));

	if (smallest == lDelta)  //leftside
	{
		_ball.ReboundX();
		_ball.Move(Vec2(rekt.left - ballRekt.right, 0.0f));
	}
	else if (smallest == rDelta)  //rightside
	{
		_ball.ReboundX();
		_ball.Move(Vec2(rekt.right - ballRekt.left, 0.0f));
	}
	if (smallest == tDelta)  //topside
	{
		_ball.ReboundY();
		_ball.Move(Vec2(0.0f, rekt.top - ballRekt.bottom));
	}
	else if (smallest == bDelta)  //bottomside
	{
		_ball.ReboundY();
		_ball.Move(Vec2(0.0f, rekt.bottom - ballRekt.top));
	}
	isDestroyed = true;
}

RectF Brick::GetRekt() const
{
	return rekt;
}

void Brick::Reset()
{
	isDestroyed = false;
}
