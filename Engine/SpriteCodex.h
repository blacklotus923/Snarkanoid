#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );
	static void DrawGameOver(const Vec2& center, Graphics& gfx);
	static void DrawHitEnter(const Vec2& center, Graphics& gfx);
	static void DrawTitle(const Vec2& center, Graphics& gfx);
	static void DrawPaddleSm(const Vec2& topleft, Graphics& gfx);
	static void DrawBox(const Vec2 & _topleft, Color c, Graphics& gfx);
	static void DrawDigits(const Vec2& _topleft, const int _digits, Color c, Graphics& gfx, bool drawBox = false);
	static void DrawOneDigit(const Vec2& _topleft, const int _digit, Color c, Graphics& gfx, bool drawBox = false);
};