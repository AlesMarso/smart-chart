#include "SC_MDIChildWindow.h"

gui::SC_MDIChildWindow::SC_MDIChildWindow()
    : SC_CommonWindowClass::SC_CommonWindowClass()
{
    m_IsClassInited = false;
    SetWindowClassName("TestMDIChild");
}

gui::SC_MDIChildWindow::~SC_MDIChildWindow()
{
    UnregisterClass(GetWindowClassName(), GetInstance());
}

bool gui::SC_MDIChildWindow::Init(const char* windowclassname, HINSTANCE hInst)
{
    SetWindowClassName(windowclassname);

    WNDCLASSEX wndMdiChildClass;

    if (GetClassInfoEx(hInst, windowclassname, &wndMdiChildClass))
        return true;

    ZeroMemory(&wndMdiChildClass, sizeof(WNDCLASSEX));

    wndMdiChildClass.cbSize = sizeof(WNDCLASSEX);
    wndMdiChildClass.hInstance = hInst;
    wndMdiChildClass.lpfnWndProc = MDIMessageHandleSetup;
    wndMdiChildClass.lpszClassName = windowclassname;

    return RegisterClassEx(&wndMdiChildClass);
}

bool gui::SC_MDIChildWindow::Create(const char* title, HWND mdiclient)
{
    MDICREATESTRUCT mdiChildWindow;

    mdiChildWindow.szClass = GetWindowClassName();
    mdiChildWindow.szTitle = title;
    mdiChildWindow.hOwner = GetInstance();
    mdiChildWindow.x = CW_USEDEFAULT;
    mdiChildWindow.y = CW_USEDEFAULT;
    mdiChildWindow.cx = CW_USEDEFAULT;
    mdiChildWindow.cy = CW_USEDEFAULT;
    mdiChildWindow.style = 0;
    mdiChildWindow.lParam = (LPARAM)this;

    HWND hwnd = (HWND)SendMessage(mdiclient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiChildWindow);

    return hwnd != nullptr;
}

bool gui::SC_MDIChildWindow::OnPaint(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIChildWindow::OnCreate(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIChildWindow::OnSize(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIChildWindow::OnClose(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIChildWindow::OnDestroy(HWND, WPARAM, LPARAM)
{
    return false;
}

bool gui::SC_MDIChildWindow::OnNcDestroy(HWND hWnd, WPARAM, LPARAM)
{
    SC_MDIChildWindow* pWnd = reinterpret_cast<SC_MDIChildWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (pWnd)
        delete pWnd;

    SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DefMDIChildProc));

    return true;
}

LRESULT gui::SC_MDIChildWindow::MDIMessageHandleSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_CREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        const MDICREATESTRUCT* const pMDICreate = reinterpret_cast<MDICREATESTRUCT*>(pCreate->lpCreateParams);

        SC_MDIChildWindow* pWnd = reinterpret_cast<SC_MDIChildWindow*>(pMDICreate->lParam);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SC_MDIChildWindow::MDIMessageHandleThunk));

        return SC_MDIChildWindow::MDIMessageHandleThunk(hWnd, msg, wParam, lParam);
    }

    return DefMDIChildProc(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_MDIChildWindow::MDIMessageHandleThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SC_MDIChildWindow* pWnd = reinterpret_cast<SC_MDIChildWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    return pWnd->MessageHandle(hWnd, msg, wParam, lParam);
}

LRESULT gui::SC_MDIChildWindow::MessageHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SC_CommonWindowClass::MessageHandle(hWnd, msg, wParam, lParam);

    return DefMDIChildProc(hWnd, msg, wParam, lParam);
}
