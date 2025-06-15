#pragma once
#include "CommonDefine.h"

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();
	virtual void Draw(const HDC& hdc) = 0;
	void Initialize(HWND hwnd);

	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
protected:
	HWND m_mainWND;
	RECT m_rectMain;
	unsigned int speedByKeyBoard;
};

