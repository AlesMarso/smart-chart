#include "Window.h"

#include "util.h"
#include "res.h"

namespace chart
{
namespace wnd
{
	Window::Window()
		: hwnd_(nullptr), wndClass_({ 0 }), instance_(nullptr), 
		x_(CW_USEDEFAULT), y_(CW_USEDEFAULT), 
		width_(CW_USEDEFAULT), height_(CW_USEDEFAULT)
	{
	}

	bool Window::Register(HINSTANCE instance)
	{
		ZeroMemory(&wndClass_, sizeof(wndClass_));

		instance_ = instance;

		wndClass_.cbSize = sizeof(WNDCLASSEXA);
		wndClass_.lpfnWndProc = Window::MessageHandlerSetup;
		wndClass_.lpszClassName = util::GetString(IDS_SMART_CHART_MAIN_WINDOW_CLASS_NAME);
		wndClass_.hInstance = instance_;

		return RegisterClassExA(&wndClass_);
	}

	bool Window::Create(HWND parent, const char* name, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		hwnd_ = CreateWindowExA(WS_EX_APPWINDOW, wndClass_.lpszClassName, name, WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE, x, y, width, height, parent, nullptr, wndClass_.hInstance, this);

		UpdateWindow(hwnd_);

		return hwnd_ != nullptr;
	}

	bool Window::Destroy()
	{
		return DestroyWindow(hwnd_) == TRUE;
	}

	uint32_t Window::GetX() const
	{
		return x_;
	}

	uint32_t Window::GetY() const
	{
		return y_;
	}

	uint32_t Window::GetWidth() const
	{
		return width_;
	}

	uint32_t Window::GetHeight() const
	{
		return height_;
	}

	LRESULT Window::OnCreate(const WndEventArgs& args)
	{
		return LRESULT();
	}

	LRESULT Window::OnSize(const WndEventArgs& args)
	{
		return LRESULT();
	}

	LRESULT Window::OnPaint(const WndEventArgs& args)
	{
		return LRESULT();
	}

	LRESULT Window::OnDestroy(const WndEventArgs& args)
	{
		return LRESULT();
	}

	LRESULT Window::OnClose(const WndEventArgs& args)
	{
		PostQuitMessage(0);
		return TRUE;
	}

	LRESULT Window::OnNcDestroy(const WndEventArgs& args)
	{
		return LRESULT();
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		WndEventArgs args = { hWnd, wParam, lParam };

		switch (msg)
		{
		case WM_CREATE:
			return OnCreate(args);

		case WM_PAINT:
			return OnPaint(args);

		case WM_SIZE:
			return OnSize(args);

		case WM_SIZING:
			return OnSize(args);

		case WM_DESTROY:
			return OnDestroy(args);

		case WM_CLOSE:
			return OnClose(args);
		}

		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::MessageHandlerSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{

		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

			Window* pWnd = static_cast<Window*>(pCreate->lpCreateParams);

			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

			break;
		}

		case WM_NCDESTROY:
		{
			Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if (pWnd)
				delete pWnd;

			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));

			break;
		}

		default:
		{
			Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			if (pWnd)
				return pWnd->MessageHandler(hWnd, msg, wParam, lParam);
		}
		}

		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::MessageHandlerThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (pWnd)
			return pWnd->MessageHandler(hWnd, msg, wParam, lParam);

		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}


}
}