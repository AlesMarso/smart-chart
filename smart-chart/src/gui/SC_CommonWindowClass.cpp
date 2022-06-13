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

HWND gui::SC_CommonWindowClass::GetHWND() const
{
	return m_hWnd;
}

HINSTANCE gui::SC_CommonWindowClass::GetInstance() const
{
	if (!m_hInstance)
		return GetModuleHandle(nullptr);

	return m_hInstance;
}

uint32_t gui::SC_CommonWindowClass::GetWidth() const
{
	return m_Width;
}

uint32_t gui::SC_CommonWindowClass::GetHeight() const
{
	return m_Height;
}

void gui::SC_CommonWindowClass::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
}

void gui::SC_CommonWindowClass::SetEvent(uint32_t event_id, uint32_t action_id, Event func)
{
	m_Events.SetEvent(event_id, action_id, func);
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

	case WM_DESTROY:
		return OnDestroy(hWnd, wParam, lParam);

	case WM_NCDESTROY:
		return OnNcDestroy(hWnd, wParam, lParam);

	case WM_COMMAND:
		return m_Events(CONTROL_ID, ACTION_ID, hWnd, wParam, lParam);
	}
}
