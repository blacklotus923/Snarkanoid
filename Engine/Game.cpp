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
	ball(Vec2(402.5f,300.0f), Vec2(0.0f,200.0f)),
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
	if (!isStarted || isGameOver)
	{
		if (musicIsPlaying)
		{
			music.StopAll();
			musicIsPlaying = false;
		}
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isStarted = true;
			isGameOver = false;
		}
	}
	else if (!isGameOver && isStarted)
	{
		if (!musicIsPlaying)
		{
			music.Play();
			musicIsPlaying = true;
		}
		float leastColDistSq = 1000000.0f;
		int indexOfCollision;
		bool collided = false;

		ball.Update(dt);
		if (ball.GetRekt().bottom >= walls.bottom)
		{
			isGameOver = true;
			ball.ReboundY();
			ball.Move(Vec2(ball.GetRekt().bottom - walls.bottom, 0.0f));
			gameOverSound.Play();
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
	}
}
