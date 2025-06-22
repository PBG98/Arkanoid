#pragma once
#include "pch.h"
#include "BaseWindow.h"
#include "CommonDefine.h"
#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Collision.h"

using namespace COMMON;

class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow();
	~MainWindow();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void CreateBlockArray();
	void MoveBlocks();
	static UINT WINAPI CreateBlocks(LPVOID pParam);
	CRITICAL_SECTION cs;

private:
	void Initialize();
	std::optional<WINDOW::Line> CheckBallCollideToWindow();
	void CheckBlocksReachPaddle();
	void DrawScore(HDC hdc);
	void ShowGameOverDialog();
	void RestartGame();
	
private:
	unique_ptr<Paddle> paddle;
	unique_ptr<Ball> ball;
	std::forward_list<unique_ptr<Block>> blocks;
	size_t blockArrayNum;

	HANDLE hThread;
	HANDLE hStopEvent;
	
	RECT rectMain;
	HDC memDC;
	HBITMAP memBitmap;
	HBITMAP oldBitmap;
	int mainWidth;
	int mainHeight;
};

