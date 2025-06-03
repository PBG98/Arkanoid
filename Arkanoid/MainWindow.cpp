#include "pch.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	InitializeCriticalSection(&cs);

	paddle = new Paddle(200, 400, 200 + COMMON::PADDLE_WIDTH, 400 + COMMON::PADDLE_HEIGHT);
	ball = new Ball(300, 300, COMMON::BALL_RADIUS);
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
	running = false;
	if (hThread)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}

	if (ball != nullptr)
	{
		delete ball;
	}
	if (paddle != nullptr)
	{
		delete paddle;
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
		SetTimer(m_hwnd, 1, 16, nullptr);
		paddle->Initialize(m_hwnd);
		ball->Initialize(m_hwnd);
		return 0;
	case WM_TIMER:
		ball->Move();
		InvalidateRect(m_hwnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
	{
		if (wParam == VK_LEFT)
		{
			paddle->MoveLeft();
		}
		else if (wParam == VK_RIGHT)
		{
			paddle->MoveRight();
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
		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks.at(i).get()->Draw(hdc);
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
	RECT rectMain;
	GetClientRect(m_hwnd, &rectMain);
	LONG mainWindowWidth = rectMain.right - rectMain.left;

	const size_t blockArrayNum = mainWindowWidth / COMMON::BLOCK_WIDTH;

	for (size_t i = 0; i < blockArrayNum; i++)
	{
		blocks.emplace_back(make_unique<Block>());
	}
}

UINT WINAPI MainWindow::CreateBlocks(LPVOID pParam)
{
	MainWindow* wnd = static_cast<MainWindow*>(pParam);

	while (wnd->running)
	{
		wnd->CreateBlockArray();

		InvalidateRect(wnd->m_hwnd, NULL, TRUE);

		Sleep(3000);
	}

	return 0;
}