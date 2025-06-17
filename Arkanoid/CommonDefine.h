#pragma once
#include "pch.h"
namespace COMMON
{
	const wstring ARKNOID = L"ARKNOID";

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
	const unsigned int WIDTH = 100;
	const unsigned int HEIGHT = 20;
}

namespace BLOCK
{
	const unsigned int WIDTH = 100;
	const unsigned int HEIGHT = 20;
}

namespace BALL
{
	const unsigned int RADIUS = 10;
}