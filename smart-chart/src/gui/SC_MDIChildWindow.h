#pragma once

#include "SC_CommonWindowClass.h"

namespace gui
{
	class SC_MDIChildWindow : public SC_CommonWindowClass
	{
	public:
		SC_MDIChildWindow();
		~SC_MDIChildWindow();

		virtual bool Init(const char*, HINSTANCE) override;
		virtual bool Create(const char*, HWND) override;
		virtual bool OnPaint(HWND, WPARAM, LPARAM);
		virtual bool OnCreate(HWND, WPARAM, LPARAM);
		virtual bool OnSize(HWND, WPARAM, LPARAM);
		virtual bool OnClose(HWND, WPARAM, LPARAM);
		virtual bool OnDestroy(HWND, WPARAM, LPARAM);
		virtual bool OnNcDestroy(HWND, WPARAM, LPARAM);

		LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM) override;

	private:
		static LRESULT MDIMessageHandleSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT MDIMessageHandleThunk(HWND, UINT, WPARAM, LPARAM);

	private:
		bool m_IsClassInited;
	};
}
