#pragma once
#include "Drawable.h"
class Ball : public Drawable
{
public:
	Ball(unsigned int x, unsigned int y, unsigned int r);
	void Draw(const HDC& hdc) override;
	void Move();

private:
	unsigned int x;
	unsigned int y;
	unsigned int r;
	int Vx;
	int Vy;
};

