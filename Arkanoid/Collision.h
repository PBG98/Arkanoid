#pragma once
#include "pch.h"
#include "CommonDefine.h"
template<typename T>
class Collision
{
public:
	static bool Check(Ball& ball, const T& stationary)
	{
		int x = ball.GetX();
		int y = ball.GetY();
		int r = ball.GetR();
		int left = stationary.GetLeft();
		int right = stationary.GetRight();
		int top = stationary.GetTop();
		int bottom = stationary.GetBottom();

		int collisionX = max(left, min(x, right));
		int collisionY = max(top, min(y, bottom));

		int distanceX = x - collisionX;
		int distanceY = y - collisionY;

		type = nullopt;

		if ((distanceX * distanceX + distanceY * distanceY) <= r * r)
		{
			if (abs(distanceX) > abs(distanceY))
			{
				if (right < x)
				{
					type = WINDOW::Collision::right;
				}
				else
				{
					type = WINDOW::Collision::left;
				}
				
			}
			else if (abs(distanceX) < abs(distanceY))
			{
				type = WINDOW::Collision::horizontal;
			}
			else
			{
				type = WINDOW::Collision::apex;
			}
		}

		if (type == nullopt)
		{
			return false;
		}

		ChangeDirection(ball, stationary);

		return true;
	}

private:
	static void ChangeDirection(Ball& ball, const T& stationary)
	{
		switch (type.value())
		{
		case WINDOW::Collision::left:
			ball.SetX(stationary.GetLeft() - ball.GetR() - 1);
			ball.ReverseVx();
			break;
		case WINDOW::Collision::right:
			ball.SetX(stationary.GetRight() + ball.GetR() + 1);
			ball.ReverseVx();
			break;
		case WINDOW::Collision::horizontal:
			ball.ReverseVy();
			break;
		case WINDOW::Collision::apex:
			ball.ReverseVx();
			ball.ReverseVy();
			break;
		default:
			break;
		}
	}

private:
	inline static optional<WINDOW::Collision> type{ nullopt };
};

