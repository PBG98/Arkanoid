#pragma once
#include "Drawable.h"
class Paddle : public Drawable
{
public:
	Paddle(int left, int top, int right, int bottom);
	void Draw(const HDC& hdc) override;
	void MoveLeft();
	void MoveRight();

private:
	int left;
	int top;
	int right;
	int bottom;
	unsigned int speed;
};

