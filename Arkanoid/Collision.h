#pragma once
#include "pch.h"
#include "CommonDefine.h"
template<typename T1, typename T2>
class Collision
{
public:
	static bool Check(T1& movable, const T2& stationary)
	{
		int x = movable.GetX();
		int y = movable.GetY();
		int r = movable.GetR();
		int left = stationary.GetLeft();
		int right = stationary.GetRight();
		int top = stationary.GetTop();
		int bottom = stationary.GetBottom();

		int collisionX = max(left, min(x, right));
		int collisionY = max(top, min(y, bottom));

		int distanceX = x - collisionX;
		int distanceY = y - collisionY;

		optional<WINDOW::Collision> type{ nullopt };

		if ((distanceX * distanceX + distanceY * distanceY) <= r * r)
		{
			if (abs(distanceX) > abs(distanceY))
			{
				type = WINDOW::Collision::vertical;
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

		switch (type.value())
		{
		case WINDOW::Collision::vertical:
			movable.ReverseVx();
			break;
		case WINDOW::Collision::horizontal:
			movable.ReverseVx();
			movable.ReverseVy();
			break;
		case WINDOW::Collision::apex:
			movable.ReverseVx();
			movable.ReverseVy();
			break;
		default:
			break;
		}

		return true;
	}

private:

};

