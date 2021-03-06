#include "SC_MDIChildWindow.h"

gui::SC_MDIChildWindow::SC_MDIChildWindow()
    : SC_CommonWindowClass::SC_CommonWindowClass()
{
    m_IsClassInited = false;
}

gui::SC_MDIChildWindow::~SC_MDIChildWindow()
{
}

const char* gui::SC_MDIChildWindow::GetWindowTitle()
{
    return utils::resource::GetResString(IDS_FINANCE_WINDOW_TITLE);
}

const char* gui::SC_MDIChildWindow::GetWindowClassName()
{
    return utils::resource::GetResString(IDS_MDI_CHILD_WINDOW_CLASS_NAME);
}

bool gui::SC_MDIChildWindow::Init(HINSTANCE hInst)
{
    WNDCLASSEX wndMdiChildClass;

    ZeroMemory(&wndMdiChildClass, sizeof(WNDCLASSEX));

    if (GetClassInfoEx(hInst, GetWindowClassName(), &wndMdiChildClass))
        return true;

    wndMdiChildClass.cbSize = sizeof(WNDCLASSEX);
    wndMdiChildClass.hInstance = hInst;
    wndMdiChildClass.lpfnWndProc = MDIMessageHandleSetup;
    wndMdiChildClass.lpszClassName = GetWindowClassName();

    return RegisterClassEx(&wndMdiChildClass);
}

bool gui::SC_MDIChildWindow::Create(HWND mdiclient)
{
    MDICREATESTRUCT mdiChildWindow;

    mdiChildWindow.szClass = GetWindowClassName();
    mdiChildWindow.szTitle = GetWindowTitle();
    mdiChildWindow.hOwner = GetInstance();
    mdiChildWindow.x = CW_USEDEFAULT;
    mdiChildWindow.y = CW_USEDEFAULT;
    mdiChildWindow.cx = CW_USEDEFAULT;
    mdiChildWindow.cy = CW_USEDEFAULT;
    mdiChildWindow.style = CS_HREDRAW | CS_VREDRAW;
    mdiChildWindow.lParam = (LPARAM)this;

    HWND hwnd = (HWND)SendMessage(mdiclient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiChildWindow);

    UpdateWindow(hwnd);

    return hwnd != nullptr;
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
