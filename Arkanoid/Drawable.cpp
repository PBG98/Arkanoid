#include "pch.h"
#include "Drawable.h"

Drawable::Drawable()
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
