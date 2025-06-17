#include "pch.h"
#include "MainWindow.h"

MainWindow::MainWindow()
	:gameStatus(COMMON::GameStatus::Ready), blockArrayNum(0), paddle(make_unique<Paddle>(200, 400)), ball(make_unique<Ball>(200 + PADDLE::WIDTH / 2, 400 - BALL::RADIUS - 1))
{
	InitializeCriticalSection(&cs);

	UINT nThreadID = 0;
	HANDLE hThread = (HANDLE)::_beginthreadex(
		NULL,
		0,
		MainWindow::CreateBlocks,
		this,
		0,
		&nThreadID
	);
}

MainWindow::~MainWindow()
{
	if (hThread)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
}

PCWSTR MainWindow::ClassName() const
{
	return COMMON::ARKNOID.c_str();
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		Initialize();
		SetTimer(m_hwnd, 1, 16, nullptr);
		paddle->Initialize(m_hwnd);
		ball->Initialize(m_hwnd);
		
		return 0;
	case WM_TIMER:
		if (gameStatus == COMMON::GameStatus::Start)
		{
			if (CheckBallCollideToWindow() == WINDOW::Line::bottom)
			{
				// Todo Game Over
			}

			Collision<Paddle>::Check(*ball, *paddle);
			blocks.remove_if([&](const auto& block) {return Collision<Block>::Check(*ball, *block); });

			ball->Move();
		}		
		InvalidateRect(m_hwnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
	{
		if (wParam == VK_SPACE)
		{
			if (gameStatus == COMMON::GameStatus::Ready ||
				gameStatus == COMMON::GameStatus::Paused)
			{
				gameStatus = COMMON::GameStatus::Start;
			}
			else
			{
				gameStatus = COMMON::GameStatus::Paused;
			}
		}

		if (wParam == VK_LEFT)
		{
			if (gameStatus == COMMON::GameStatus::Ready ||
				gameStatus == COMMON::GameStatus::Start)
			{
				paddle->MoveLeft();
			}

			if (gameStatus == COMMON::GameStatus::Ready)
			{
				ball->MoveLeft();
			}
		}

		if (wParam == VK_RIGHT)
		{
			if (gameStatus == COMMON::GameStatus::Ready ||
				gameStatus == COMMON::GameStatus::Start)
			{
				paddle->MoveRight();
			}

			if (gameStatus == COMMON::GameStatus::Ready)
			{
				ball->MoveRight();
			}
		}
		InvalidateRect(m_hwnd, NULL, TRUE);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (MessageBox(m_hwnd, L"Really quit?", COMMON::ARKNOID.c_str(), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(m_hwnd);
		}
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		paddle->Draw(hdc);
		ball->Draw(hdc);
		for (const auto& block : blocks)
		{
			block.get()->Draw(hdc);
		}

		EndPaint(m_hwnd, &ps);
		return 0;
	}
	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}

void MainWindow::CreateBlockArray()
{
	for (size_t i = 0; i < blockArrayNum; i++)
	{
		int leftPoint = i * BLOCK::WIDTH;
		blocks.emplace_front(make_unique<Block>(leftPoint));
	}
}

UINT WINAPI MainWindow::CreateBlocks(LPVOID pParam)
{
	MainWindow* wnd = static_cast<MainWindow*>(pParam);

	while (true)
	{
		if (wnd->gameStatus == COMMON::GameStatus::Start)
		{
			wnd->CreateBlockArray();
			wnd->MoveBlocks();

			InvalidateRect(wnd->m_hwnd, NULL, TRUE);

			Sleep(8000);
		}	
	}

	return 0;
}

void MainWindow::Initialize()
{
	RECT rectMain;
	GetClientRect(m_hwnd, &rectMain);
	LONG mainWindowWidth = rectMain.right - rectMain.left;

	blockArrayNum = mainWindowWidth / BLOCK::WIDTH;
}

std::optional<WINDOW::Line> MainWindow::CheckBallCollideToWindow()
{
	RECT rectMain;
	GetClientRect(m_hwnd, &rectMain);

	int x = ball.get()->GetX();
	int y = ball.get()->GetY();
	int r = ball.get()->GetR();

	if (x - r <= rectMain.left + 2)
	{
		ball.get()->ReverseVx();
		return WINDOW::Line::left;
	}

	if (x + r >= rectMain.right)
	{
		ball.get()->ReverseVx();
		return WINDOW::Line::right;
	}

	if (y - r <= rectMain.top + 2)
	{
		ball.get()->ReverseVy();
		return WINDOW::Line::top;
	}

	if (y + r >= rectMain.bottom)
	{
		ball.get()->ReverseVy();
		return WINDOW::Line::bottom;
	}

	return nullopt;
}

void MainWindow::MoveBlocks()
{
	for (const auto& block : blocks)
	{
		block.get()->Move();
	}
}
