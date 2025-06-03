#include "pch.h"
#include "Ball.h"

Ball::Ball(unsigned int x, unsigned int y, unsigned int r)
	:x(x), y(y), r(r)
{
	Vx = 1;
	Vy = 1;
}

void Ball::Draw(const HDC& hdc)
{
	int right = x + r;
	int left = x - r;
	int top = y + r;
	int bottom = y - r;
	
	Ellipse(hdc, left, top, right, bottom);
}

void Ball::Move()
{
	x += Vx;
	y += Vy;
}
