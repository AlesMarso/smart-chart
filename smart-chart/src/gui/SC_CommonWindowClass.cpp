#include "SC_CommonWindowClass.h"

constexpr uint32_t WINDOW_WIDTH_DEF = 1500;
constexpr uint32_t WINDOW_HEIGHT_DEF = 900;

gui::SC_CommonWindowClass::SC_CommonWindowClass()
	: m_hInstance(GetModuleHandle(nullptr)),
	m_hWnd(nullptr),
	m_Width(WINDOW_WIDTH_DEF),
	m_Height(WINDOW_HEIGHT_DEF)
{
}

gui::SC_CommonWindowClass::~SC_CommonWindowClass()
{
}

bool gui::SC_CommonWindowClass::Init(HINSTANCE hInst)
{
	m_hInstance = hInst;

	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = MessageHandleSetup;
	wndClass.lpszClassName = m_WindowClassName;
	wndClass.lpszMenuName = MAKEINTRESOURCEA(IDR_MAIN_MENU);

	return RegisterClassEx(&wndClass);
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
	return nullptr;
}

uint32_t gui::SC_CommonWindowClass::GetWidth() const
{
	return m_Width;
}

uint32_t gui::SC_CommonWindowClass::GetHeight() const
{
	return m_Height;
}

const char* gui::SC_CommonWindowClass::GetWindowClassName() const
{
	return (const char*)m_WindowClassName;
}

void gui::SC_CommonWindowClass::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
}

void gui::SC_CommonWindowClass::SetWindowTitle(const char* title)
{
	SetWindowText(m_hWnd, title);
}

void gui::SC_CommonWindowClass::SetWindowClassName(const char* class_name)
{
	m_WindowClassName = (char*)class_name;
}

void gui::SC_CommonWindowClass::SetEvent(uint32_t event_id, uint32_t action_id, Event func)
{
	m_Events.SetEvent(event_id, action_id, func);
}

LRESULT gui::SC_CommonWindowClass::MessageHandleSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		SC_CommonWindowClass* pWnd = static_cast<SC_CommonWindowClass*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SC_CommonWindowClass::MessageHandleThunk));
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_CommonWindowClass::MessageHandleThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SC_CommonWindowClass* const pWnd = reinterpret_cast<SC_CommonWindowClass*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->MessageHandle(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_CommonWindowClass::MessageHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		return OnCreate(hWnd, wParam, lParam);

	case WM_PAINT:
		return OnPaint(hWnd, wParam, lParam);

	case WM_SIZE:
		return OnSize(hWnd, wParam, lParam);

	case WM_CLOSE:
		return OnClose(hWnd, wParam, lParam);

	case WM_COMMAND:
		return m_Events(CONTROL_ID, ACTION_ID, hWnd, wParam, lParam);
	}
}
