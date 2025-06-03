#pragma once
class Drawable
{
public:
	Drawable();
	virtual ~Drawable();
	virtual void Draw(const HDC& hdc) = 0;
	void Initialize(HWND hwnd);

protected:
	HWND m_mainWND;
	RECT m_rectMain;
};

