#include "pch.h"
#include "Block.h"

Block::Block(int left)
	: left(left), top(-(int)BLOCK::HEIGHT), speed(BLOCK::HEIGHT)
{
	right = left + BLOCK::WIDTH;
	bottom = top + BLOCK::HEIGHT;
}

Block::~Block()
{
}

void Block::Draw(const HDC& hdc)
{
	Rectangle(hdc, left, top, right, bottom);
}

void Block::Move()
{
	top += speed;
	bottom += speed;
}

int Block::GetLeft() const
{
	return left;
}

int Block::GetRight() const
{
	return right;
}

int Block::GetTop() const
{
	return top;
}

int Block::GetBottom() const
{
	return bottom;
}
