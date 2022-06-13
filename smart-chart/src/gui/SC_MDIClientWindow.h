#pragma once

#include "SC_CommonWindowClass.h"
#include "SC_MDIChildWindow.h"
#include "SC_OpenGLChart.h"

namespace gui
{
	class SC_MDIClientWindow : public SC_CommonWindowClass
	{
	public:
		SC_MDIClientWindow();
		~SC_MDIClientWindow();

		const char* GetWindowTitle() override;
		const char* GetWindowClassName() override;

		bool Init(HINSTANCE) override;
		bool Create(HWND) override;

		bool OnPaint(HWND, WPARAM, LPARAM) override;
		bool OnCreate(HWND, WPARAM, LPARAM) override;
		bool OnSize(HWND, WPARAM, LPARAM) override;
		bool OnClose(HWND, WPARAM, LPARAM) override;
		bool OnDestroy(HWND, WPARAM, LPARAM) override;
		bool OnNcDestroy(HWND, WPARAM, LPARAM) override;
		bool OnEraseBackground(HWND, WPARAM, LPARAM) override;

		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM) override;

	public:
		bool OnNewFinanceChart(HWND, WPARAM, LPARAM);
		bool OnNewFunctionChart(HWND, WPARAM, LPARAM);
		bool OnMDIDestroy(HWND, WPARAM, LPARAM);
		bool CreateMdiChild(SC_MDIChildWindow*);

	private:
		static LRESULT MDIClientMessageHandleSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MDIClientMessageHandleThunk(HWND, UINT, WPARAM, LPARAM);

	private:
		HWND m_hWndMDIClient;
	};

}
