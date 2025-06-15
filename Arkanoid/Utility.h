#pragma once
class Utility
{
public:
	Utility();
	~Utility();
	
	// 원과 사각형 충돌 감지
	bool IsBallCollide(int cx, int cy, int r, int left, int top, int right, int bottom);
};

