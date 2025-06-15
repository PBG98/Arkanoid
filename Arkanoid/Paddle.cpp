#include "pch.h"
#include "Paddle.h"

Paddle::Paddle(int left, int top)
	:left(left), top(top)
{
	right = left + PADDLE::WIDTH;
	bottom = top + PADDLE::HEIGHT;
}

void Paddle::Draw(const HDC& hdc)
{
	Rectangle(hdc, left, top, right, bottom);
}

void Paddle::MoveLeft()
{
	if (left > m_rectMain.left)
	{
		left -= speedByKeyBoard;
		right -= speedByKeyBoard;
	}
}

void Paddle::MoveRight()
{
	if (right < m_rectMain.right)
	{
		left += speedByKeyBoard;
		right += speedByKeyBoard;
	}
}

int Paddle::GetLeft() const
{
	return left;
}

int Paddle::GetRight() const
{
	return right;
}

int Paddle::GetTop() const
{
	return top;
}

int Paddle::GetBottom() const
{
	return bottom;
}
