#pragma once

#include <Windows.h>
#include <cstdint>

namespace gui
{
	class SC_CommonWindowClass
	{
	public:
		SC_CommonWindowClass();
		SC_CommonWindowClass(HINSTANCE);
		~SC_CommonWindowClass();

	public:
		bool Init(const char*);
		bool Init(HINSTANCE, const char*);

		HWND GetHWND() const;
		HINSTANCE GetInstance() const;
		const char* GetWindowTitle();

		int Run();

	public:
		virtual bool OnPaint(WPARAM, LPARAM);
		virtual bool OnCreate(WPARAM, LPARAM);
		virtual bool OnSize(WPARAM, LPARAM);
		virtual bool OnClose(WPARAM, LPARAM);

	private:
		static LRESULT MessageHandleSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MessageHandleThunk(HWND, UINT, WPARAM, LPARAM);

		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM);

	private:
		HWND			m_hWnd;
		HINSTANCE		m_hInstance;
		LPCSTR			m_WindowTitle;
		LPCSTR			m_WindowClassName;
		WNDCLASSEX		m_WndClass;

		uint32_t		m_Width;
		uint32_t		m_Height;
	};
}
