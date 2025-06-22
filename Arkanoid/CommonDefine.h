#pragma once
#include "pch.h"
namespace COMMON
{
	const wstring ARKNOID = L"ARKNOID";

	const size_t LIFE = 3;

	const size_t BLOCK_CREATE_TIME = 7000;

	const size_t INTIAL_POINT_LEFT = 200;
	const size_t INTIAL_POINT_TOP = 400;

	const size_t KEBOARD_SPEED = 20;

	enum class GameStatus
	{
		Ready,
		Start,
		Paused,
		End
	};
}

namespace WINDOW
{
	enum class Line
	{
		left,
		right,
		top,
		bottom
	};

	enum class Collision
	{
		left,
		right,
		horizontal,
		apex
	};
}

namespace PADDLE
{
	const size_t WIDTH = 100;
	const size_t HEIGHT = 20;
}

namespace BLOCK
{
	const size_t WIDTH = 100;
	const size_t HEIGHT = 20;
}

namespace BALL
{
	const size_t RADIUS = 10;
	const size_t SPEED_X = 4;
	const size_t SPEED_Y = -4;
}