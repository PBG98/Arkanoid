#pragma once
#include "pch.h"
#include "CommonDefine.h"
template<typename T1, typename T2>
class Collision
{
public:
	static optional<WINDOW::Collision> Check(const T1& movalbe, const T2& staionary)
	{
		return nullopt;
	}

private:
	optional<WINDOW::Collision> IsBallCollide(int cx, int cy, int r, int left, int top, int right, int bottom)
	{
		int collisionX = max(left, min(cx, right));
		int collisionY = max(top, min(cy, bottom));

		int distanceX = cx - collisionX;
		int distanceY = cy - collisionY;

		if ((distanceX * distanceX + distanceY * distanceY) <= r * r)
		{
			if (abs(distanceX) > abs(distanceY))
			{
				return WINDOW::Collision::vertical;
			}
			else if (abs(distanceX) < abs(distanceY))
			{
				return WINDOW::Collision::horizontal;
			}
			else
			{
				return WINDOW::Collision::apex;
			}
		}

		return nullopt;
	}

};

