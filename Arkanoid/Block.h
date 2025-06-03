#pragma once
#include "Drawable.h"

class Block : public Drawable
{
public:
	Block();
	void Draw(const HDC& hdc) override;

private:
	int left;
	int top;
	int right;
	int bottom;
	unsigned int speed;
};

