#include "pch.h"
#include "Paddle.h"

Paddle::Paddle(int left, int top, int right, int bottom)
	:left(left), top(top), right(right), bottom(bottom)
{
	speed = 10;
}

void Paddle::Draw(const HDC& hdc)
{
	Rectangle(hdc, left, top, right, bottom);
}

void Paddle::MoveLeft()
{
	if (left > m_rectMain.left)
	{
		left -= speed;
		right -= speed;
	}
}

void Paddle::MoveRight()
{
	if (right < m_rectMain.right)
	{
		left += speed;
		right += speed;
	}
}
