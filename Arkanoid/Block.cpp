#include "pch.h"
#include "Block.h"

Block::Block()
	: left(0), right(100), top(0), bottom(20), speed(0)
{
	speed = 5;
}

void Block::Draw(const HDC& hdc)
{
	Rectangle(hdc, left, top, right, bottom);
}
