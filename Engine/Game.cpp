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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(0.0f, (float)Graphics::ScreenWidth, (float)Graphics::ScreenHeight, 0.0f),
	ball(Vec2(402.5f,300.0f), Vec2(-200.0f,-200.0f)),
	paddle(Vec2((float)Graphics::ScreenWidth/2,(float) Graphics::ScreenHeight-75),45.0f,10.0f),
	paddleSound(L"Sounds\\arkpad.wav"),
	brickSound(L"Sounds\\arkbrick.wav")
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
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	float leastColDistSq = 1000000.0f;
	int indexOfCollision;
	bool collided = false;

	ball.Update(dt);
	if(ball.DoWallCollision(walls)) paddle.ResetCooldown();

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

	if(paddle.DoBallCollision(ball)) paddleSound.Play();
	paddle.Update(wnd.kbd, wnd.mouse, dt, walls);
}

void Game::ComposeFrame()
{
	for (Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	ball.Draw(gfx);
	paddle.Draw(gfx);
}
