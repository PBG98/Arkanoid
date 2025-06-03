#include "pch.h"
#include "MainWindow.h"
#include "CommonDefine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(COMMON::ARKNOID.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg{};

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}