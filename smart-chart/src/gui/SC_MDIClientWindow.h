#pragma once

#include "SC_CommonWindowClass.h"

namespace gui
{
	class SC_MDIClientWindow : public SC_CommonWindowClass
	{
	public:
		SC_MDIClientWindow();
		~SC_MDIClientWindow();

		bool Init(HINSTANCE) override;
		bool Create(const char*, HWND) override;

		bool OnPaint(HWND, WPARAM, LPARAM) override;
		bool OnCreate(HWND, WPARAM, LPARAM) override;
		bool OnSize(HWND, WPARAM, LPARAM) override;
		bool OnClose(HWND, WPARAM, LPARAM) override;

		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM) override;

	private:
		HWND m_hWndMDIClient;
	};

}
