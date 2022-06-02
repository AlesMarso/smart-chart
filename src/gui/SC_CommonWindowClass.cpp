#include "SC_CommonWindowClass.h"

gui::SC_CommonWindowClass::SC_CommonWindowClass()
	: m_hInstance(GetModuleHandle(nullptr)),
	m_hWnd(nullptr)
{
	m_WindowTitle = "Smart Chart";
	m_WindowClassName = "SmartChartMarsoWindowClassName";
}

gui::SC_CommonWindowClass::SC_CommonWindowClass(HINSTANCE hInst)
	: m_hWnd(nullptr)
{
	m_hInstance = hInst;

	m_WindowTitle = "Smart Chart";
	m_WindowClassName = "SmartChartMarsoWindowClassName";
}

gui::SC_CommonWindowClass::~SC_CommonWindowClass()
{
}

bool gui::SC_CommonWindowClass::Init(const char*)
{
	return false;
}

HWND gui::SC_CommonWindowClass::GetHWND() const
{
	return m_hWnd;
}

HINSTANCE gui::SC_CommonWindowClass::GetInstance() const
{
	return m_hInstance;
}

const char* gui::SC_CommonWindowClass::GetWindowTitle()
{
	return m_WindowTitle;
}
