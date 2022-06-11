#include "SC_MDIClientWindow.h"

gui::SC_MDIClientWindow::SC_MDIClientWindow()
	: SC_CommonWindowClass::SC_CommonWindowClass(),
	m_hWndMDIClient(nullptr)
{
}

gui::SC_MDIClientWindow::~SC_MDIClientWindow()
{
}

bool gui::SC_MDIClientWindow::Init(HINSTANCE hInst)
{
	SetWindowClassName("SmartChartMDIClientWindowClassName");

	return SC_CommonWindowClass::Init(hInst);
}

bool gui::SC_MDIClientWindow::Create(const char* title, HWND parent = nullptr)
{
	HWND hwnd = CreateWindowEx(0,
		GetWindowClassName(), title,
		WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, GetWidth(), GetHeight(),
		nullptr, nullptr, GetInstance(), this);

	if (!hwnd)
		return false;

	SetHWND(hwnd);

	return true;
}

bool gui::SC_MDIClientWindow::OnPaint(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIClientWindow::OnCreate(HWND hWnd, WPARAM, LPARAM)
{
	CLIENTCREATESTRUCT mdiClient;

	mdiClient.hWindowMenu = nullptr;
	mdiClient.idFirstChild = 50000;

	m_hWndMDIClient = CreateWindow(
		TEXT("MDICLIENT"),
		(LPCSTR)nullptr,
		WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
		0, 0, 0, 0,
		hWnd, 
		nullptr, 
		GetInstance(), 
		(LPVOID)&mdiClient);

    return m_hWndMDIClient != nullptr;
}

bool gui::SC_MDIClientWindow::OnSize(HWND hWnd, WPARAM, LPARAM)
{
	if (m_hWndMDIClient)
	{
		RECT clientRect;
		if (GetClientRect(hWnd, &clientRect))
		{
			MoveWindow(
				m_hWndMDIClient,
				0, 0,
				clientRect.left - clientRect.right,
				clientRect.top - clientRect.bottom,
				true);
		}
	}

    return false;
}

bool gui::SC_MDIClientWindow::OnClose(HWND, WPARAM, LPARAM)
{
	PostQuitMessage(0);
    return true;
}

LRESULT gui::SC_MDIClientWindow::MessageHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SC_CommonWindowClass::MessageHandle(hWnd, msg, wParam, lParam);

	if (m_hWndMDIClient)
		return DefFrameProc(hWnd, m_hWndMDIClient, msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}
