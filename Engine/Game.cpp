/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#undef min

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(fieldOffset, fieldWidth+fieldOffset, (float)Graphics::ScreenHeight, border),
	ball(Vec2(402.5f,300.0f), Vec2(0.0f,0.0f)),
	paddle(Vec2((float)Graphics::ScreenWidth/2,(float) Graphics::ScreenHeight-75),44.0f,8.0f),
	paddleSound(L"Sounds\\pad2.wav"),
	brickSound(L"Sounds\\brick2.wav"),
	gameOverSound(L"Sounds\\gameover.wav"),
	music(L"Sounds\\bgmusic.wav",0.11f,108.05f)
{
	for (Brick& b : bricks)
	{
		int x = (int)(&b - &bricks[0]) % gridWidth;  //I'm sorry but this is fucking awesome.
		int y = (int)(&b - &bricks[0]) / gridWidth;  //subtract reference addresses to get the index of the current reference in the array WHAT?!
		b=Brick(RectF(Vec2(x*bWidth+offsetX, y*bHeight+offsetY), bWidth, bHeight), colors[y%6]);
	}

}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f) //consume small chunks of time until frametime is consumed (then consume the tiny last bite) and run physics
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (curLives < 0) isGameOver = true;
	if (!isStarted || isGameOver)
	{
		if (musicIsPlaying)
		{
			music.StopAll();
			musicIsPlaying = false;
		}
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			for (Brick& b : bricks)
			{
				b.Reset();
			}
			isStarted = true;
			isGameOver = false;
			ball.Reset();
			curLives = StartExtraLives;
		}
	}
	else if (!isGameOver && isStarted )
	{
		if (!musicIsPlaying)
		{
			music.Play();
			musicIsPlaying = true;
		}
		float leastColDistSq = 1000000.0f;
		int indexOfCollision;
		bool collided = false;
		if (ball.IsLaunched())
		{
			ball.Update(dt);
			if (ball.GetRekt().bottom >= walls.bottom)
			{
					ball.ReboundY();
					ball.Move(Vec2(ball.GetRekt().bottom - walls.bottom, 0.0f));
					gameOverSound.Play();
					curLives -= 1;
					ball.Reset();
			}
			else if (ball.DoWallCollision(walls)) paddle.ResetCooldown();

			for (Brick& b : bricks)
			{
				if (b.CheckBallCollision(ball))
				{
					float collisionDist = (b.GetRekt().GetCenter() - ball.GetRekt().GetCenter()).GetLengthSq();
					if (collisionDist < leastColDistSq)
					{
						leastColDistSq = collisionDist;
						indexOfCollision = (int)(&b - &bricks[0]);
					}
					collided = true;
				}
			}
			if (collided)
			{
				paddle.ResetCooldown();
				bricks[indexOfCollision].DoBallCollision(ball);
				brickSound.Play();
			}

			if (paddle.DoBallCollision(ball)) paddleSound.Play();
			paddle.Update(wnd.kbd, wnd.mouse, dt, walls);
		}
		else
		{
			paddle.Update(wnd.kbd, wnd.mouse, dt, walls);
			ball.MoveTo(paddle.GetRekt().GetCenter() + Vec2(0.0f, -14.0f));
			if (wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed())
			{
				ball.SetVelocity(Vec2(0.0f, -200.0f));
				ball.Launch(200.0f);
			}
		}
	}
}

void Game::DrawBorder()
{
	int bx = (int)(walls.left - border-1);
	int by = (int)(walls.top - border);
	for (int y = by; y <= walls.bottom + border; y++)
	{
		for (int x = bx; x <= walls.right + border; x++)
		{
			if (x >= 0 && x < Graphics::ScreenWidth
				&& y >= 0 && y < Graphics::ScreenHeight)
			{
				if (y <= walls.top || x < walls.left-1 || x > walls.right || y > walls.bottom)
				{
					gfx.PutPixel(x, y, borderColor);
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	DrawBorder();
	if (!isStarted)
	{
		SpriteCodex::DrawTitle(Vec2((float)gfx.ScreenWidth / 2.0f, (float)gfx.ScreenHeight / 2.0f), gfx);
		SpriteCodex::DrawHitEnter(Vec2((float)gfx.ScreenWidth / 2.0f, ((float)gfx.ScreenHeight / 2.0f)+53.0f), gfx);
	}
	else if (isGameOver)
	{
		SpriteCodex::DrawGameOver(Vec2((float)gfx.ScreenWidth / 2.0f, (float)gfx.ScreenHeight / 2.0f), gfx);
		SpriteCodex::DrawHitEnter(Vec2((float)gfx.ScreenWidth / 2.0f, ((float)gfx.ScreenHeight / 2.0f) + 62.0f), gfx);
	}
	else
	{
		for (Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		ball.Draw(gfx);
		paddle.Draw(gfx);
		DrawLives(Vec2(walls.left - 70.0f, Graphics::ScreenHeight - 45.0f), curLives);
	}
}

void Game::DrawLives(const Vec2& _topleft, const int _lives)
{
	//paddleSmall	= 48x12
	//x				= 11x10
	//numbers		= 8x14
	Color c;
	if (_lives < 1) c = Colors::Red;
	else c = Colors::White;
	SpriteCodex::DrawPaddleSm(_topleft,gfx); //draw at topleft
	int tempLives = _lives;
	int numDigits = 0; do { tempLives /= 10; numDigits++; } while (tempLives > 0);
	const int x = (int)_topleft.x + 24 - ((13 + (10 * numDigits)) / 2);  //draw x-centered on paddle
	const int y = (int)_topleft.y+22;  //draw under paddle
	{
		gfx.PutPixel(0 + x, 0 + y, c);
		gfx.PutPixel(1 + x, 0 + y, c);
		gfx.PutPixel(2 + x, 0 + y, c);
		gfx.PutPixel(3 + x, 0 + y, c);
		gfx.PutPixel(7 + x, 0 + y, c);
		gfx.PutPixel(8 + x, 0 + y, c);
		gfx.PutPixel(9 + x, 0 + y, c);
		gfx.PutPixel(10 + x, 0 + y, c);
		gfx.PutPixel(2 + x, 1 + y, c);
		gfx.PutPixel(8 + x, 1 + y, c);
		gfx.PutPixel(3 + x, 2 + y, c);
		gfx.PutPixel(7 + x, 2 + y, c);
		gfx.PutPixel(4 + x, 3 + y, c);
		gfx.PutPixel(6 + x, 3 + y, c);
		gfx.PutPixel(5 + x, 4 + y, c);
		gfx.PutPixel(4 + x, 5 + y, c);
		gfx.PutPixel(6 + x, 5 + y, c);
		gfx.PutPixel(3 + x, 6 + y, c);
		gfx.PutPixel(7 + x, 6 + y, c);
		gfx.PutPixel(2 + x, 7 + y, c);
		gfx.PutPixel(8 + x, 7 + y, c);
		gfx.PutPixel(0 + x, 8 + y, c);
		gfx.PutPixel(1 + x, 8 + y, c);
		gfx.PutPixel(2 + x, 8 + y, c);
		gfx.PutPixel(3 + x, 8 + y, c);
		gfx.PutPixel(7 + x, 8 + y, c);
		gfx.PutPixel(8 + x, 8 + y, c);
		gfx.PutPixel(9 + x, 8 + y, c);
		gfx.PutPixel(10 + x, 8 + y, c);
	}//drawX - 11x10
	const Vec2(digits) = Vec2((float)x+14.0f, (float)y-4.0f);  //draw to the right of x, centered
	SpriteCodex::DrawDigits(digits, _lives, c, gfx, true);
}