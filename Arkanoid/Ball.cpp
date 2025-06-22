#include "pch.h"
#include "Ball.h"

Ball::Ball(unsigned int x, unsigned int y)
	:x(x), y(y)
{
	r = BALL::RADIUS;
	Vx = 8;
	Vy = -8;
}

void Ball::Draw(const HDC& hdc)
{
	Ellipse(hdc, x - r, y + r, x + r, y - r);
}

void Ball::Move()
{
	x += Vx;
	y += Vy;
}

void Ball::MoveLeft()
{
	if (x - r > m_rectMain.left)
	{
		x -= speedByKeyBoard;
	}
}

void Ball::MoveRight()
{
	if (x + r < m_rectMain.right)
	{
		x += speedByKeyBoard;
	}
}

int Ball::GetX() const
{
	return x;
}

int Ball::GetY() const
{
	return y;
}

int Ball::GetR() const
{
	return r;
}

void Ball::SetX(const int x)
{
	this->x = x;
}

void Ball::SetY(const int y)
{
	this->y = y;
}

void Ball::ReverseVx()
{
	Vx = -Vx;
}

void Ball::ReverseVy()
{
	Vy = -Vy;
}
