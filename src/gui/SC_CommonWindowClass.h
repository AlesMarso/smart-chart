#pragma once

#include <Windows.h>

namespace gui
{
	class SC_CommonWindowClass
	{
	public:
		SC_CommonWindowClass();
		SC_CommonWindowClass(HINSTANCE);
		~SC_CommonWindowClass();

		bool Init(const char*);

		HWND GetHWND() const;
		HINSTANCE GetInstance() const;
		const char* GetWindowTitle();

	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		LPCSTR m_WindowTitle;
		LPCSTR m_WindowClassName;

		
	};
}
