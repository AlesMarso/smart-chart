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
		bool Init();
		bool Init(HINSTANCE);

		bool Create(const char*);

		int Run();

		HWND GetHWND() const;
		HINSTANCE GetInstance() const;
		const char* GetWindowTitle();

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	public:
		bool OnPaint(WPARAM, LPARAM);
		bool OnCreate(WPARAM, LPARAM);
		bool OnSize(WPARAM, LPARAM);
		bool OnClose(WPARAM, LPARAM);

	private:
		static LRESULT MessageHandleSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MessageHandleThunk(HWND, UINT, WPARAM, LPARAM);

	protected:
		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM);

	private:
		HWND		m_hWnd;
		HINSTANCE	m_hInstance;
		LPCSTR		m_WindowTitle;
		LPCSTR		m_WindowClassName;
		WNDCLASSEX	m_WndClass;

		uint32_t	m_Width;
		uint32_t	m_Height;
	};
}
