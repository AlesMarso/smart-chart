#include "SC_MDIClientWindow.h"

gui::SC_MDIClientWindow::SC_MDIClientWindow()
	: SC_CommonWindowClass::SC_CommonWindowClass(),
	m_hWndMDIClient(nullptr)
{
}

gui::SC_MDIClientWindow::~SC_MDIClientWindow()
{
	UnregisterClass(GetWindowClassName(), GetInstance());
	UnregisterClass(utils::resource::GetResString(IDS_MDI_CHILD_WINDOW_CLASS_NAME), GetInstance());
}

const char* gui::SC_MDIClientWindow::GetWindowTitle()
{
	return utils::resource::GetResString(IDS_MDI_FRAME_WINDOW_NAME);
}

const char* gui::SC_MDIClientWindow::GetWindowClassName()
{
	return utils::resource::GetResString(IDS_MDI_FRMAE_WINDOW_CLASS_NAME);
}

bool gui::SC_MDIClientWindow::Init(HINSTANCE hInst)
{
	SetEvent(ID_CHART_FINANCE, ID_ACTION_MAIN_MENU, BIND_EVENT(SC_MDIClientWindow::OnNewFinanceChart));

	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = MDIClientMessageHandleSetup;
	wndClass.lpszClassName = GetWindowClassName();
	wndClass.lpszMenuName = MAKEINTRESOURCEA(IDR_MAIN_MENU);

	return RegisterClassEx(&wndClass);
}

bool gui::SC_MDIClientWindow::Create(HWND parent = nullptr)
{
	HWND hwnd = CreateWindow(
		GetWindowClassName(), 
		GetWindowTitle(),
		WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		GetWidth(), 
		GetHeight(),
		parent, 
		nullptr, 
		GetInstance(), 
		this);

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
	mdiClient.idFirstChild = IDM_FIRSTCHILD;

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
			MoveWindow(m_hWndMDIClient, 0, 0, clientRect.right, clientRect.bottom, true);
	}

    return true;
}

bool gui::SC_MDIClientWindow::OnClose(HWND, WPARAM, LPARAM)
{
	PostQuitMessage(0);
    return true;
}

bool gui::SC_MDIClientWindow::OnDestroy(HWND, WPARAM, LPARAM)
{
	return true;
}

bool gui::SC_MDIClientWindow::OnNcDestroy(HWND hWnd, WPARAM, LPARAM)
{
	SC_MDIClientWindow* const pWnd = reinterpret_cast<SC_MDIClientWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (pWnd)
		delete pWnd;

	SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DefWindowProc));

	return true;
}

bool gui::SC_MDIClientWindow::OnNewFinanceChart(HWND, WPARAM, LPARAM)
{
	SC_MDIChildWindow* pFinanceChart = new SC_MDIChildWindow();

	if (pFinanceChart->Init(GetInstance()))
		return pFinanceChart->Create(m_hWndMDIClient);

	return false;
}

bool gui::SC_MDIClientWindow::OnMDIDestroy(HWND, WPARAM, LPARAM)
{
	return false;
}

LRESULT gui::SC_MDIClientWindow::MessageHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MDIDESTROY:
		OnMDIDestroy(hWnd, wParam, lParam);
		break;

	default:
		SC_CommonWindowClass::MessageHandle(hWnd, msg, wParam, lParam);
		break;
	}

	if (m_hWndMDIClient)
		return DefFrameProc(hWnd, m_hWndMDIClient, msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_MDIClientWindow::MDIClientMessageHandleSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		SC_MDIClientWindow* pWnd = static_cast<SC_MDIClientWindow*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SC_MDIClientWindow::MDIClientMessageHandleThunk));
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_MDIClientWindow::MDIClientMessageHandleThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SC_MDIClientWindow* const pWnd = reinterpret_cast<SC_MDIClientWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->MessageHandle(hWnd, msg, wParam, lParam);
}
