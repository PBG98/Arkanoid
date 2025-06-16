#pragma once
#include "Drawable.h"

class Block : public Drawable
{
public:
	Block(int left);
	~Block();
	void Draw(const HDC& hdc) override;
	void Move();

	void MoveLeft() override {};
	void MoveRight() override {};

	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

private:
	int left;
	int right;
	int top;
	int bottom;
	unsigned int speed;
};

