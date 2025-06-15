#include "pch.h"
#include "Utility.h"

Utility::Utility()
{
}

Utility::~Utility()
{
}

bool Utility::IsBallCollide(int cx, int cy, int r, int left, int top, int right, int bottom)
{
	int collisionX = max(left, min(cx, right));
	int collisionY = max(top, min(cy, bottom));

	int distanceX = cx - collisionX;
	int distanceY = cy - collisionY;

	if ((distanceX * distanceX + distanceY * distanceY) <= r * r)
	{
		return true;
	}

	return false;
}
