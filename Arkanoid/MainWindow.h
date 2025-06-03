#pragma once
#include "pch.h"
#include "BaseWindow.h"
#include "CommonDefine.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow();
	~MainWindow();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void CreateBlockArray();
	static UINT WINAPI CreateBlocks(LPVOID pParam);
	bool running = true;

private:
	Paddle* paddle;
	Ball* ball;
	vector<unique_ptr<Block>> blocks;

	CRITICAL_SECTION cs;
	HANDLE hThread;
	
};

