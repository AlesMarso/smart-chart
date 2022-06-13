#pragma once

#include "SC_CommonWindowClass.h"

namespace gui
{
	class SC_MDIChildWindow : public SC_CommonWindowClass
	{
	public:
		SC_MDIChildWindow();
		~SC_MDIChildWindow();

		const char* GetWindowTitle() override;
		const char* GetWindowClassName() override;

		virtual bool Init(HINSTANCE) override;
		virtual bool Create(HWND) override;
		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM) override;

		virtual bool OnClose(HWND, WPARAM, LPARAM);
		virtual bool OnDestroy(HWND, WPARAM, LPARAM);
		virtual bool OnNcDestroy(HWND, WPARAM, LPARAM);

	private:
		static LRESULT MDIMessageHandleSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MDIMessageHandleThunk(HWND, UINT, WPARAM, LPARAM);

	private:
		bool m_IsClassInited;
	};
}
