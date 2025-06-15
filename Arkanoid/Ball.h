#pragma once
#include "Drawable.h"
class Ball : public Drawable
{
public:
	Ball(unsigned int x, unsigned int y);
	void Draw(const HDC& hdc) override;
	void Move();

	void MoveLeft() override;
	void MoveRight() override;

	int GetX() const;
	int GetY() const;
	int GetR() const;

	void ReverseVx();
	void ReverseVy();	

private:
	int x;
	int y;
	int r;
	int Vx;
	int Vy;
};

