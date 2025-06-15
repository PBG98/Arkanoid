#pragma once
#include "Drawable.h"
class Paddle : public Drawable
{
public:
	Paddle(int left, int top);
	void Draw(const HDC& hdc) override;
	void MoveLeft() override;
	void MoveRight() override;

	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

private:
	int left;
	int top;
	int right;
	int bottom;
};

