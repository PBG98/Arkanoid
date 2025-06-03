#pragma once
#include "pch.h"

template<class DERIVED_TYPE>
class BaseWindow
{
public:
	BaseWindow();
	virtual ~BaseWindow();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, HWND hWndParent = 0, HMENU hMenu = 0);
	HWND Window() const;

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	HWND m_hwnd;
};

template<class DERIVED_TYPE>
inline BaseWindow<DERIVED_TYPE>::BaseWindow()
	:m_hwnd(nullptr)
{
}

template<class DERIVED_TYPE>
inline BaseWindow<DERIVED_TYPE>::~BaseWindow()
{
}

template<class DERIVED_TYPE>
inline LRESULT BaseWindow<DERIVED_TYPE>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DERIVED_TYPE* pThis = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = (DERIVED_TYPE*)(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

		pThis->m_hwnd = hwnd;
	}
	else
	{
		pThis = reinterpret_cast<DERIVED_TYPE*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
	{
		return pThis->HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

template<class DERIVED_TYPE>
inline BOOL BaseWindow<DERIVED_TYPE>::Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
{
	WNDCLASS wc{ 0 };
	wc.lpfnWndProc = BaseWindow::WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = ClassName();

	RegisterClass(&wc);

	RECT rc{ 0, 0, 700, 480 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	nWidth = rc.right - rc.left;
	nHeight = rc.bottom - rc.top;

	m_hwnd = CreateWindowEx(dwExStyle, ClassName(), lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this);

	return (m_hwnd ? TRUE : FALSE);
}

template<class DERIVED_TYPE>
inline HWND BaseWindow<DERIVED_TYPE>::Window() const
{
	return m_hwnd;
}
