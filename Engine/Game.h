/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float bWidth = 40.0f;
	static constexpr float bHeight = 18.0f;
	static constexpr int gridWidth = 13;
	static constexpr int gridHeight = 10;
	static constexpr float offsetX = (Graphics::ScreenWidth - (bWidth*gridWidth)) / 2.0f;
	static constexpr float offsetY = 25.0f;
	static constexpr float fieldWidth = bWidth*gridWidth;
	static constexpr float fieldOffset = (Graphics::ScreenWidth - fieldWidth) / 2.0f;
	Color colors[6] = {Color(116,133,38), Color(120,31,22), Color(6,34,69), Color(26,103,196), Color(196,33,17), Color(172,172,172) };
	Brick bricks[gridHeight * gridWidth];
	Ball ball;
	FrameTimer ft;
	RectF walls;
	Paddle paddle;
	Sound paddleSound;
	Sound brickSound;
	Sound music;
	Sound gameOverSound;
	bool musicIsPlaying = false;
	bool isGameOver = false;
	bool isStarted = false;
	/********************************/
};