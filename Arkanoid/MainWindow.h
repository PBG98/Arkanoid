#pragma once
#include "pch.h"
#include "BaseWindow.h"
#include "CommonDefine.h"
#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Collision.h"
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

private:
	void Initialize();
	std::optional<WINDOW::Line> CheckBallCollideToWindow();
	void DrawScore(HDC hdc);
	void ShowGameOverDialog();
	void RestartGame();
private:
	unique_ptr<Paddle> paddle;
	unique_ptr<Ball> ball;
	std::forward_list<unique_ptr<Block>> blocks;

	CRITICAL_SECTION cs;
	HANDLE hThread;
	size_t blockArrayNum;

	static HANDLE hStopEvent;
};

