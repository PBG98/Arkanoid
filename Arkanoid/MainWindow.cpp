#include "pch.h"
#include "MainWindow.h"

MainWindow::MainWindow()
	:blockArrayNum(0)
{
	InitializeCriticalSection(&cs);

	UINT nThreadID = 0;
	hThread = (HANDLE)::_beginthreadex(
		NULL,
		0,
		MainWindow::CreateBlocks,
		this,
		0,
		&nThreadID
	);

	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

MainWindow::~MainWindow()
{
	if (hStopEvent)
	{
		SetEvent(hStopEvent);
	}
	
	if (hThread)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		hThread = nullptr;
	}

	DeleteCriticalSection(&cs);

	if (hStopEvent)
	{
		CloseHandle(hStopEvent);
		hStopEvent = nullptr;
	}
}

PCWSTR MainWindow::ClassName() const
{
	return ARKNOID.c_str();
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		Initialize();
		SetTimer(m_hwnd, 1, 16, nullptr);
		
		return 0;
	case WM_TIMER:
		if (GameManager::GetInstance().CheckGameStatus(GameStatus::Start))
		{
			if (CheckBallCollideToWindow() == WINDOW::Line::bottom)
			{
				GameManager::GetInstance().DecreaseLife();
				Initialize();
				if (GameManager::GetInstance().IsGameOver())
				{
					GameManager::GetInstance().UpdateGameStatus(GameStatus::End);
					ShowGameOverDialog();
				}
				return 0;
			}

			Collision<Paddle>::Check(*ball, *paddle);

			EnterCriticalSection(&cs);
			size_t score = blocks.remove_if([&](const auto& block) {return Collision<Block>::Check(*ball, *block); });
			LeaveCriticalSection(&cs);

			GameManager::GetInstance().IncreaseScore(score);

			ball->Move();

			CheckBlocksReachPaddle();
		}		
		InvalidateRect(m_hwnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
	{
		if (wParam == VK_SPACE)
		{
			if (GameManager::GetInstance().CheckGameStatus(GameStatus::Ready) ||
				GameManager::GetInstance().CheckGameStatus(GameStatus::Paused))
			{
				GameManager::GetInstance().UpdateGameStatus(GameStatus::Start);
			}
			else
			{
				GameManager::GetInstance().UpdateGameStatus(GameStatus::Paused);
			}
		}

		if (wParam == VK_LEFT)
		{
			if (GameManager::GetInstance().CheckGameStatus(GameStatus::Ready) ||
				GameManager::GetInstance().CheckGameStatus(GameStatus::Start))
			{
				paddle->MoveLeft();
			}

			if (GameManager::GetInstance().CheckGameStatus(GameStatus::Ready))
			{
				ball->MoveLeft();
			}
		}

		if (wParam == VK_RIGHT)
		{
			if (GameManager::GetInstance().CheckGameStatus(GameStatus::Ready) ||
				GameManager::GetInstance().CheckGameStatus(GameStatus::Start))
			{
				paddle->MoveRight();
			}

			if (GameManager::GetInstance().CheckGameStatus(GameStatus::Ready))
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
		if (MessageBox(m_hwnd, L"Really quit?", ARKNOID.c_str(), MB_OKCANCEL) == IDOK)
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
		EnterCriticalSection(&cs);
		for (const auto& block : blocks)
		{
			block.get()->Draw(hdc);
		}
		LeaveCriticalSection(&cs);

		DrawScore(hdc);

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
		size_t leftPoint = i * BLOCK::WIDTH;
		blocks.emplace_front(make_unique<Block>(leftPoint));
	}
}

UINT WINAPI MainWindow::CreateBlocks(LPVOID pParam)
{
	MainWindow* wnd = static_cast<MainWindow*>(pParam);

	while (WaitForSingleObject(wnd->hStopEvent, 0) != WAIT_OBJECT_0)
	{
		if (GameManager::GetInstance().CheckGameStatus(GameStatus::Start))
		{
			EnterCriticalSection(&wnd->cs);
			wnd->CreateBlockArray();
			wnd->MoveBlocks();
			LeaveCriticalSection(&wnd->cs);

			InvalidateRect(wnd->m_hwnd, NULL, TRUE);
		}

		if (WaitForSingleObject(wnd->hStopEvent, BLOCK_CREATE_TIME) != WAIT_TIMEOUT)
			break;
	}

	return 0;
}

void MainWindow::Initialize()
{
	if (paddle != nullptr)
	{
		paddle.reset();
	}
	if (ball != nullptr)
	{
		ball.reset();
	}
	EnterCriticalSection(&cs);
	if (!blocks.empty())
	{
		blocks.clear();
	}
	LeaveCriticalSection(&cs);
	paddle = make_unique<Paddle>(INTIAL_POINT_LEFT, INTIAL_POINT_TOP);
	ball = make_unique<Ball>(INTIAL_POINT_LEFT + PADDLE::WIDTH / 2, INTIAL_POINT_TOP - BALL::RADIUS - 1);
	paddle->Initialize(m_hwnd);
	ball->Initialize(m_hwnd);

	GameManager::GetInstance().UpdateGameStatus(GameStatus::Ready);

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

void MainWindow::CheckBlocksReachPaddle()
{
	bool anyBlockReached = false;

	EnterCriticalSection(&cs);
	blocks.remove_if([&](const auto& block) {
		if (block->GetBottom() > paddle->GetTop())
		{
			anyBlockReached = true;
			return true;
		}
		return false;
		});
	LeaveCriticalSection(&cs);

	if (anyBlockReached)
	{
		GameManager::GetInstance().DecreaseLife();
		if (GameManager::GetInstance().IsGameOver())
		{
			GameManager::GetInstance().UpdateGameStatus(GameStatus::End);
			ShowGameOverDialog();
		}
	}
}

void MainWindow::DrawScore(HDC hdc)
{
	HFONT hFont = CreateFont(
		24,
		0,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		L"Arial"
	);

	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));
	wstring scoreText = to_wstring(GameManager::GetInstance().GetScore());

	RECT clientRect;
	GetClientRect(m_hwnd, &clientRect);

	RECT textRect;
	textRect.left = clientRect.right - 150;
	textRect.top = 10;
	textRect.right = clientRect.right - 10;
	textRect.bottom = 50;

	DrawText(hdc, scoreText.c_str(), -1, &textRect, DT_RIGHT | DT_TOP);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void MainWindow::ShowGameOverDialog()
{
	unsigned int finalSocre = GameManager::GetInstance().GetScore();

	wstring message = L"Game Over!\n\Final Score: " + to_wstring(finalSocre) + L"\n\nPlay Again?";

	int result = MessageBox(
		m_hwnd,
		message.c_str(),
		L"Game Over",
		MB_OKCANCEL | MB_ICONINFORMATION
	);

	if (result == IDOK)
	{
		RestartGame();
	}
	else
	{
		PostQuitMessage(0);
	}
}

void MainWindow::RestartGame()
{
	GameManager::GetInstance().Reset();
	Initialize();
}

void MainWindow::MoveBlocks()
{
	for (const auto& block : blocks)
	{
		block.get()->Move();
	}
}
