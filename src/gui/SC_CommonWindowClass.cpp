#include "SC_CommonWindowClass.h"

constexpr uint32_t WINDOW_WIDTH_DEF = 600;
constexpr uint32_t WINDOW_HEIGHT_DEF = 500;

gui::SC_CommonWindowClass::SC_CommonWindowClass()
	: m_hInstance(GetModuleHandle(nullptr)),
	m_hWnd(nullptr),
	m_WindowTitle(nullptr),
	m_Width(WINDOW_WIDTH_DEF),
	m_Height(WINDOW_HEIGHT_DEF)
{
	m_WindowClassName = "SmartChartMarsoWindowClassName";
	ZeroMemory(&m_WndClass, sizeof(m_WndClass));
}

gui::SC_CommonWindowClass::SC_CommonWindowClass(HINSTANCE hInst)
	: m_hWnd(nullptr),
	m_WindowTitle(nullptr),
	m_Width(WINDOW_WIDTH_DEF),
	m_Height(WINDOW_HEIGHT_DEF)
{
	m_hInstance = hInst;

	m_WindowClassName = "SmartChartMarsoWindowClassName";

	ZeroMemory(&m_WndClass, sizeof(m_WndClass));
}

gui::SC_CommonWindowClass::~SC_CommonWindowClass()
{
}

bool gui::SC_CommonWindowClass::Init(const char* title)
{
	m_WindowTitle = title;

	m_WndClass.cbSize = sizeof(WNDCLASSEX);
	m_WndClass.hInstance = m_hInstance;
	m_WndClass.lpfnWndProc = MessageHandleSetup;
	m_WndClass.lpszClassName = m_WindowClassName;

	return RegisterClassEx(&m_WndClass);
}

bool gui::SC_CommonWindowClass::Init(HINSTANCE hInst, const char* title)
{
	m_hInstance = hInst;
	
	return Init(title);
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

int gui::SC_CommonWindowClass::Run()
{
	m_hWnd = CreateWindowEx(0,
		m_WindowClassName, m_WindowTitle,
		WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
		nullptr, nullptr, m_hInstance, this);
	
	if (m_hWnd == nullptr)
	{
		return -1;
	}
	
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		if (msg.message == WM_QUIT)
			return static_cast<int>(msg.wParam);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

bool gui::SC_CommonWindowClass::OnPaint(WPARAM, LPARAM)
{
	return false;
}

bool gui::SC_CommonWindowClass::OnCreate(WPARAM, LPARAM)
{
	return false;
}

bool gui::SC_CommonWindowClass::OnSize(WPARAM, LPARAM)
{
	return false;
}

bool gui::SC_CommonWindowClass::OnClose(WPARAM, LPARAM)
{
	PostQuitMessage(0);
	return false;
}

LRESULT gui::SC_CommonWindowClass::MessageHandleSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		SC_CommonWindowClass* pWnd = static_cast<SC_CommonWindowClass*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SC_CommonWindowClass::MessageHandleThunk));
		
		return pWnd->MessageHandle(hWnd, msg, wParam, lParam);
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
	case WM_CLOSE:
		return OnClose(wParam, lParam);

	case WM_CREATE:
		return OnCreate(wParam, lParam);

	case WM_PAINT:
		return OnPaint(wParam, lParam);

	case WM_SIZE:
		return OnSize(wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
