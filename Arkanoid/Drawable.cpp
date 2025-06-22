#include "pch.h"
#include "Drawable.h"

Drawable::Drawable()
	:m_mainWND(nullptr), m_rectMain(0), speedByKeyBoard(20)
{
	
}

Drawable::~Drawable()
{
}

void Drawable::Initialize(HWND hwnd)
{
	m_mainWND = hwnd;
	GetClientRect(m_mainWND, &m_rectMain);
}
